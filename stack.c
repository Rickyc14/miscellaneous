#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXC   1024
#define MAXNM    64


struct stack_node{
    int value;
    char *name;
    struct stack_node * next;
};
typedef struct stack_node stack_node;

struct stack{
    stack_node *top;
    int size;
};
typedef struct stack stack;

stack *create_stack()
{
    stack *s = malloc (sizeof *s);
    if (!s) {
        perror ("malloc-s");
        return NULL;
    }

    s->size = 0;
    s->top = NULL;

    return s;
}

int empty_stack (stack * s) {
    return s->size == 0;
}


stack_node *push_stack (stack *s, int value, char *name) /// ****
{
    stack_node *n = malloc (sizeof *n);
    if (!n) {
        perror ("malloc-n");
        return NULL;
    }

    n->value = value;
    n->name = malloc (strlen (name) + 1);
    if (!n->name) {
        perror ("malloc-name");
        return NULL;
    }
    strcpy (n->name, name);
    n->next = s->top; /// ****
    s->top = n;
    s->size++;

    return n;
}

stack_node *pop_stack (stack *s)
{
    if (s->size > 0) {
        stack_node *node = s->top;
        s->top = s->top->next;
        s->size--;
        return node;
    }

    return NULL;
}

void free_node (stack_node *n)
{
    if (n->name)
        free (n->name);

    free (n);
}

void free_stack (stack *s)
{
    while (s->size > 0) {
        stack_node *victim = s->top;
        s->top = s->top->next;
        free_node (victim);
        s->size--;
    }

    free (s);
}

int main (void) {

    stack *s = create_stack();
    stack_node *node = NULL;

    if (!s)         /* validate !!! */
        return 1;

    for (;;) {      /* loop continually taking input until exit conditon */
        char buf[MAXC]  = "",   /* line buffer for fgets */
            name[MAXNM] = "";   /* buffer for parsing name from line */
        int value = 0;          /* int to parse from line */

        for (;;) {  /* loop continually until you get valid int */
            fputs ("\nenter value: ", stdout);  /* prompt for value */
            if (fgets (buf, MAXC, stdin)) {     /* validate line read */
                if (sscanf (buf, "%d", &value) == 1) { /* convert to int */
                    if (value == 0) {   /* your exit condition */
                        fputs ("  value == 0 (input done)\n", stderr );
                        goto inputdone; /* jump out of both loops */
                    }
                    break;
                }
                else    /* non-integer (non-numeric) input */
                    fputs ("  error: invalid integer input.\n", stderr);
            }
            else {  /* fgets returned EOF (user canceled) */
                fputs ("(user canceled input)\n", stderr);
                goto inputdone; /* jump out of both loops */
            }
        }

        for (;;) {      /* loop continually until name recieved */
            fputs ("enter name : ", stdout);        /* prompt name */
            if (fgets (name, MAXNM, stdin)) {       /* read name */
                size_t len = strlen (name);         /* get length */
                if (len && name[len-1] == '\n') {   /* last char \n ? */
                    name[--len] = 0;                /* overwrite with \0 */
                    if (len)                    /* check 1 char remains */
                        break;                  /* got good name, go push */
                    else    /* user just pressed [Enter] */
                        fputs ("  error: empty-line.\n", stderr);
                }
                else if (len == MAXNM -1)   /* was input too long? */
                    fputs ("  warning: name truncated.\n", stderr);
            }
            else {  /* fgets returned EOF (user canceled) */
                fputs ("(user canceled input)\n", stderr);
                goto inputdone; /* jump out of both loops */
            }
        }

        push_stack (s, value, name);    /* push value and name on stack */
    }
    inputdone:;

    puts ("\nvalues stored in stack\n");
    while ((node = pop_stack(s)) != NULL) {
        printf ("value:  %2d    name: %s\n", node->value, node->name);
        free_node (node);   /* free node */
    }
    free_stack (s);     /* free stack */

    return 0;
}
