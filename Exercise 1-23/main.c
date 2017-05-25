#include <stdio.h>
#include <stdlib.h>

#define P   0 // Program
#define PC  1 // Program - Comment
#define S   2 // String
#define E   3 // Escape  (in Strings)
#define CS  4 // Comment (simple)
#define CM  5 // Comment (multiple lines)
#define CMP 6 // Comment (multiple lines) - Program

void update_transition(char c);

//global STATE; start in state P
int STATE = P;

int main(int argc, char** argv) {

    int c;

    while ((c = getchar()) != EOF) {
        update_transition(c);
    }

    return 0;
}

void update_transition(char c) {

    if (STATE == P) {
        if (c == '/') {
            STATE = PC;
            return;
        }
        if (c == '"') {
            STATE = S;
            printf("%c", c);
            return;
        }
        printf("%c", c);
        return;
    } else if (STATE == PC) {
        if (c != '/' && c != '*') {
            STATE = P;
            printf("/%c", c);
            return;
        }
        if (c == '/') STATE = CS;
        if (c == '*') STATE = CM;
        return;
    } else if (STATE == CS) {
        if (c == '\n') {
            STATE = P;
            printf("%c", c);
        }
        return;
    } else if (STATE == CM) {
        if (c == '*') STATE = CMP;
        return;
    } else if (STATE == CMP) {
        if (c == '/') STATE = P;
        if (c != '/' && c != '*') STATE = CM;
        return;
    } else if (STATE == S) {
        if (c == '"') STATE = P;
        if (c == '\\') STATE = E;
        printf("%c", c);
        return;
    } else if (STATE == E) {
        STATE = S;
        printf("%c", c);
        return;
    }

}
