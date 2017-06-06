#include <stdio.h>

int getch(void);
void ungetch(int);

main() {

    int c, p;

    printf("Type in one character: ");
    c = getch();
    printf("Reading: %c\n", c);
    ungetch(c);
    printf("ungetch called\n");
    printf("Reading again: %c\n", getch());

    return 0;
}


char b = 0; /* push back character for ungetch */

int getch(void) /* get a (possibly pushed back) character */ {
    if (b == 0)
        getchar();
    else {
        int c = b;
        b = 0;
        return c;
    }
}

void ungetch(int c) /* push character back on input */ {
    if (b != 0)
        printf("ungetch: too many characters\n");
    else
        b = c;
}


