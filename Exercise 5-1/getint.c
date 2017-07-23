#include <stdio.h>

#define SIZE 10

void ungetch(int c);

int main(int argc, char** argv) {

    int n, array[SIZE], getint(int*);

    for (n=0; n < SIZE && getint(&array[n]) != EOF; n++)
        printf("%d\n", array[n]);

    return 0;
}


#include <ctype.h>

int getint(int *pn);
int getch(void);

/* getint: get next integer from input into *pn */
int getint(int *pn) {

    int c, sign;

    while (isspace(c = getch())) /* skip white space */
        ;
    if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
        ungetch(c); /*it's not a number */
        return 0;
    }
    sign = (c == '-') ? -1 : 1;
    if (c == '+' || c == '-') {
        int ch = getch();
        if (!isdigit(ch)) { 
            if (ch != EOF)
                ungetch(ch);
            ungetch(c);
            return c;
        }
        c = ch;
    }
    for (*pn = 0; isdigit(c); c = getch())
        *pn = 10 * *pn + (c - '0');
    *pn *= sign;
    if (c != EOF)
        ungetch(c);
    return c;
}


#define BUFSIZE 100

char buf[BUFSIZE]; /* buffer for ungetch */
int bufp = 0; /* next free position in buf */

int getch(void) /* get a (possibly pushed back) character */ {
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) /* push character back on input */ {
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}
