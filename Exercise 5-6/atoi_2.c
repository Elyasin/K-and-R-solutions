#include <stdio.h>

int a_to_i(char s[]);

int main(int argc, char** argv) {

    int n;
    char s[] = "-12345";

    n = a_to_i(s);
    printf("%d\n", n);

    return 0;
}

#include <ctype.h>

/* atoi:  convert s to integer; version 2 */
int a_to_i(char s[]) {
    int n, sign;

    for (; isspace(*s); s++) /* skip white space */
        ;
    sign = (*s == '-') ? -1 : 1;
    if (*s == '+' || *s == '-') /* skip sign */
        s++;
    for (n = 0; isdigit(*s); s++)
        n = 10 * n + (*s - '0');
    return sign * n;
}
