#include <stdio.h>

#define MAXLINE 100

double a_to_f(char s[]);

main() {

    char s[MAXLINE] = "-1.95e-2";
    printf("Converting %s\n", s);

    double d = a_to_f(s);
    printf("%g\n", d);

    return 0;
}

#include <ctype.h>

/* atof:  convert string s to double */
double a_to_f(char s[]) {

    double val, power, exp_val;
    int i, j, sign, exp_sign, exp_int;

    for (i = 0; isspace(s[i]); i++) /* skip white space */
        ;
    sign = (s[i] == '-') ? -1 : 1;
    if (s[i] == '+' || s[i] == '-')
        i++;
    for (val = 0.0; isdigit(s[i]); i++)
        val = 10.0 * val + (s[i] - '0');
    if (s[i] == '.')
        i++;
    for (power = 1.0; isdigit(s[i]); i++) {
        val = 10.0 * val + (s[i] - '0');
        power *= 10.0;
    }

    if (s[i] == 'e' || s[i] == 'E')
        i++;
    exp_sign = (s[i] == '-') ? -1 : 1;
    if (s[i] == '+' || s[i] == '-')
        i++;
    for (exp_int = 0; isdigit(s[i]); i++)
        exp_int = 10 * exp_int + (s[i] - '0');
    if (exp_sign == -1)
        for (j = 0, exp_val = 1; j < exp_int; j++)
            exp_val /= 10.0;
    else
        for (j = 0, exp_val = 1; j < exp_int; j++)
            exp_val *= 10.0;

    return sign * val / power * exp_val;
}
