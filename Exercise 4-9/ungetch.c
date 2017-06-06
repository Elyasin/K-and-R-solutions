#include <stdio.h>

int getch(void);
void ungetch(int);

main() {

    int c, p;

    printf("Type Ctrl-d\n");
    c = getch();
    printf("Reading: %d\n", c);
    ungetch(c);
    printf("ungetch called\n");
    printf("Reading again: %d\n", getch());

    return 0;
}



#define BUFSIZE 100

int buf[BUFSIZE];  /* buffer for ungetch */
int bufp = 0;       /* next free position in buf */

int getch(void) /* get a (possibly pushed back) character */ {
    return (bufp > 0) ? buf[--bufp] : getchar(); 
}

void ungetch(int c) /* push character back on input */ {
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}


