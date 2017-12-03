#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXLINE 100

void minscanf(char *fmt, ...) {
    va_list ap; /* points to each unnamed arg in turn */
    char fmt_chars[MAXLINE];
    char *p, *sval, *cval;
    int *ival, i;
    unsigned int *uval;
    float *fval;

    va_start(ap, fmt); /* make ap point to 1st unnamed arg */
    i = 0;
    for (p = fmt; *p; p++) {
        if (*p != '%') {
            fmt_chars[i++] = *p;
            continue;
        }
        fmt_chars[i++] = '%';
        while ( *(p+1) && !isalpha(*(p+1)) )
            fmt_chars[i++] = *++p;
        fmt_chars[i++] = *(p+1);
        fmt_chars[i] = '\0';
        switch (*++p) {
            case 'd':
            case 'i':
                ival = va_arg(ap, int*);
                scanf(fmt_chars, ival);
                break;
            case 'u':
            case 'x':
            case 'X':
            case 'o':
                uval = va_arg(ap, unsigned int *);
                scanf(fmt_chars, uval);
                break;
            case 'f':
                fval = va_arg(ap, float*);
                scanf(fmt_chars, fval);
                break;
            case 's':
                sval = va_arg(ap, char *);
                scanf(fmt_chars, sval);
                break;
            case 'c':
                cval = va_arg(ap, char*);
                scanf(fmt_chars, cval);
                break;
            case 'e':
                fval = va_arg(ap, float*);
                scanf(fmt_chars, fval);
                break;
            case 'E':
                fval = va_arg(ap, float*);
                scanf(fmt_chars, fval);
                break;
            case 'g':
                fval = va_arg(ap, float*);
                scanf(fmt_chars, fval);
                break;
            case 'G':
                fval = va_arg(ap, float*);
                scanf(fmt_chars, fval);
                break;
            default:
                scanf("", fmt_chars);
                break;
        }
        i = 0; //reset
    }
    va_end(ap); /* clean up when done */
}

int main(int argc, char** argv) {

    unsigned int u;
    int i1, i2;
    float f1, f2;
    double d;
    char c;
    char s[1000];


    printf("Type in two integers. The second integer can be octal or hexadecimal.\n");
    minscanf("%d %i", &i1, &i2);
    printf("Integer: %d %i\n", i1, i2);
    
    printf("Type in an unsigned integers\n");
    minscanf("%u", &u);
    printf("Unsigned: %u\n", u);
    
    printf("Type in two floating point numbers\n");
    minscanf("%f %f", &f1, &f2);
    printf("Float: %f %f\n", f1, f2);
   
    printf("Type in a string. A string is read until the next white space.\n");
    minscanf("%s", s);
    printf("String: %s\n", s);
    
    printf("Type in an octal number\n");
    minscanf("%o", &i1);
    printf("Octal: %d\n", i1);
    
    printf("Type in a hexadecimal number\n");
    minscanf("%x", &i1);
    printf("Hexadecimal: %d\n", i1);
    
    printf("Type in a hexadecimal number\n");
    minscanf("%X", &i1);
    printf("Hexadecimal: %d\n", i1);
    
    printf("Type in a character");
    minscanf("%c", &c);
    printf("(Newline consumed)\n");
    minscanf("%c", &c);
    printf("Char: %c\n", c);
    
    printf("Type in two exponential numbers\n");
    minscanf("%e %E", &f1, &f2);
    printf("Exponentials: %e %E\n", f1, f2);
    
    printf("Type in two exponential numbers\n");
    minscanf("%g %G", &f1, &f2);
    printf("Exponentials: %g %G\n", f1, f2);

    return 0;
}

