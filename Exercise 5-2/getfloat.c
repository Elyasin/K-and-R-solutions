#include <stdio.h>

#define SIZE 10


int main(int argc, char** argv) {

    int n, getfloat(float*);
    float array[SIZE];

    for (n=0; n < SIZE && getfloat(&array[n]) != EOF; n++)
        printf("n = %g\n", array[n]);

    return 0;
}


int getch(void);
void ungetch(int);

/* getfloat: get next float from input into *pf */
int getfloat(float *pf) {

    int c, sign, i;
    float fraction;

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
    for (*pf = 0; isdigit(c); c = getch())
        *pf = 10 * *pf + (c - '0');
    if (c == '.')
        c = getch();
    for (i = 10; isdigit(c); c = getch(), i *= 10)
        fraction += ((c - '0') / (float) i);
    *pf += fraction;
    *pf *= sign;
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
