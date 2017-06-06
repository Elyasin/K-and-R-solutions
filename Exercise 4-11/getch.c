#include <stdio.h>

#define BUFSIZE 100

char buf[BUFSIZE];  /* buffer for ungetch */
int bufp = 0;       /* next free position in buffer */


int getch(void) /* get a (possibly pushed back) character */ {

    return (bufp > 0) ? buf[--bufp] : getchar();

}

