#include <stddef.h>
#include <string.h>
#include <stdio.h>

char* reverse_string(char* string) {
    if (string == NULL)
        return string;

    size_t length = strlen(string);
    char *fwd = string;
    char *rev = &string[length - 1];

    while (rev > fwd) {
        char tmp = *rev;
        *rev-- = *fwd;
        *fwd++ = tmp;
    }
    return string;
}

int main() {
    char s[] = "some cool string";
    reverse_string(s);
    printf("Reversed string: %s\n", s);
    return 0;
}

