#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>

#define MAXLINE 100

/* minprintf:  minimal printf with variable argument list */
void minprintf(char *fmt, ...) {
    va_list ap; /* points to each unnamed arg in turn */
    char fmt_chars[MAXLINE];
    int n;
    char *p, *sval;
    int ival;
    unsigned uval;
    double dval;

    va_start(ap, fmt); /* make ap point to 1st unnamed arg */
    for (p = fmt; *p; p++) {
        if (*p != '%') {
            putchar(*p);
            continue;
        }
        n = 0;
        fmt_chars[n++] = '%';
        while ( *(p+1) && !isalpha(*(p+1)) )
            fmt_chars[n++] = *++p;
        fmt_chars[n++] = *(p+1);
        fmt_chars[n] = '\0';
        switch (*++p) {
            case 'd':
            case 'i':
            case 'c':
                ival = va_arg(ap, int);
                printf(fmt_chars, ival);
                break;
            case 'u':
                uval = va_arg(ap, unsigned);
                printf(fmt_chars, uval);
                break;
            case 'f':
                dval = va_arg(ap, double);
                printf(fmt_chars, dval);
                break;
            case 's':
                for (sval = va_arg(ap, char *); *sval; sval++)
                    putchar(*sval);
                break;
            case 'o':
            case 'O':
            case 'x':
            case 'X':
                ival = va_arg(ap, int);
                printf(fmt_chars, ival);
                break;
            case 'e':
            case 'E':
            case 'g':
            case 'G':
                dval = va_arg(ap, double);
                printf(fmt_chars, dval);
                break;
            default:
                printf("%s", fmt_chars+1);
                break;
        }
    }
    va_end(ap); /* clean up when done */
}

int main() {

    minprintf("Integers: %d, %i\n", 1, 2);
    minprintf("Unsigned: %u\n", ~0);
    minprintf("Float: %f\n", 1.23456789);
    minprintf("String: %s\n", "Hello World!");
    minprintf("Octal: %o\n", 63);
    minprintf("Hexadecimal: %x\n", 255);
    minprintf("Hexadecimal: %X\n", 255);
    minprintf("Char (newline): %c", '\n');
    minprintf("Exponential: %e\n", 300e6);
    minprintf("Exponential: %E\n", 6626e-37);
    minprintf("%%g: %g\n", 300000000.);
    minprintf("%%G: %G\n", 0.000005);
    minprintf("Percentage symbol: %%\n");
    
    return 0;
}

