#include <stdio.h>

/* Macro. Suitable only for ASCII character set
 * Faster, but takes more space for program code
 * due to macro expansion.
 *
 * Can be problematic if c has side effects.
 * It appears twice.
 */
#define isupper_macro(c) ((c >= 'A') && (c <= 'Z') ? 1 : 0)

/* Function declaration */
int isupper_function(char);


int main(int argc, char** argv) {

    char c = 'B';
    
    printf("isupper_macro(%c): %d\n", c, isupper_macro(c));
    printf("isupper_function(%c): %d\n", c, isupper_function(c));
    c = 'b'; 
    printf("isupper_macro(%c): %d\n", c, isupper_macro(c));
    printf("isupper_function(%c): %d\n", c, isupper_function(c));

    return 0;
}


/* 
 * Function: Suitable only for ASCII character set.
 * Takes less space for program code, but slower due 
 * to function call overhead
 */
int isupper_function(char c) {
    return (c >= 'A' && c <= 'Z');
}

