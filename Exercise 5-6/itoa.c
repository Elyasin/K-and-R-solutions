#include <stdio.h>

void itoa(int n, char s[]);

int main(int argc, char** argv) {

    char s[20];
    int n = -123456789;

    itoa(n, s);
    printf("%s\n", s);

    return 0;
}

void reverse(char s[]);

/* itoa:  convert n to characters in s */
void itoa(int n, char s[]) {

    int sign;
    char *p = s;

    if ((sign = n) < 0) /* record sign */
        n = -n; /* make n positive */

    do { /* generate digits in reverse order */
        *s++ = n % 10 + '0'; /* get next digit */
    } while ((n /= 10) > 0); /* delete it */
    if (sign < 0)
        *s++ = '-';
    *s = '\0';
    reverse(p);
}

#include <string.h>

/* reverse:  reverse string s in place */
void reverse(char s[]) {
    int c;
    char *p, *q;
    for (p = s, q = s + strlen(s) - 1; p < q; p++, q--)
        c = *p, *p = *q, *q = c;
}
