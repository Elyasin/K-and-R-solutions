#include <stdio.h>
#include <ctype.h>
#include "calc.h"


/* getop:  get next operator or numeric operand */
int getop(char s[]) {
    int i, c;

    /* use static internal variable as buffer */
    static int c_buf = 0;

    if (c_buf == 0)
        c = getch();
    else {
        c = c_buf;
        c_buf = 0;
    }

    while ((s[0] = c) == ' ' || c == '\t')
        c = getch();
    s[1] = '\0';

    if ('A' <= c && c <= 'Z')
        return SET_VAR;
    if ('a' <= c && c <= 'z')
        return GET_VAR;

    if (!isdigit(c) && c != '.' && c != '-')
        return c;
    if (c == '-') { // possible negative number
        if (!isdigit(s[0] = c = getch())) { // minus operator
            if (c != EOF)
                c_buf = c;
            s[0] = c = '-';
            return c;
        } else { // negative number
            s[0] = '-';
            s[1] = c;
            i = 1;
        }
    } else
        i = 0; // positive number
    if (isdigit(c)) /* collect integer part */
        while (isdigit(s[++i] = c = getch()))
            ;
    if (c == '.') /* collect fraction part */
        while (isdigit(s[++i] = c = getch()))
            ;
    s[i] = '\0';
    if (c != EOF)
        c_buf = c;

    return NUMBER;
}
