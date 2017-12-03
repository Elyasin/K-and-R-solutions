#include <stdio.h>

/* Macro. Suitable only for ASCII character set */
#define isupper_macro(c) ((c >= 'A') && (c <= 'Z'))

int main(int argc, char** argv) {

    char c = 'B';
    
    printf("isupper_macro(%c): %d\n", c, isupper_macro('B'));
    printf("isupper(%c): %d\n", c, isupper_macro('B'));
    
    return 0;
}

/* Function: Suitable only for ASCII character set. */
int isupper(char c) {
    return c <= 'A' && c >= 'Z';
}

