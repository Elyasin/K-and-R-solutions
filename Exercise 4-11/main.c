#include <stdio.h>
#include <stdlib.h> /* for atof */
#include <math.h>
#include <errno.h>
#include "calc.h"

#define MAXOP 100 /* max size of operand or operator */

/* reverse Polish calculator */
main() {
    int type, i;
    double op2;
    char s[MAXOP];
    double var[ALPHA];

    for (i = 0; i < ALPHA; i++)
        var[i] = 0.0;

    while ((type = getop(s)) != EOF) {
        switch (type) {
            case NUMBER:
                push(atof(s));
                break;
            case SET_VAR: // set the variable to stack's top value
                op2 = top();
                var[s[0] - 'A'] = op2;
                break;
            case GET_VAR: // replace variable by its value
                push(var[s[0] - 'a']);
                break;
            case '+':
                push(pop() + pop());
                break;
            case '*':
                push(pop() * pop());
                break;
            case '-':
                op2 = pop();
                push(pop() - op2);
                break;
            case '/':
                op2 = pop();
                if (op2 != 0.0)
                    push(pop() / op2);
                else
                    printf("error: zero divisor\n");
                break;
            case '%':
                op2 = pop();
                if (op2 != 0.0)
                    push((int) pop() % (int) op2);
                else
                    printf("error: zero divisor\n");
                break;
            case SINUS:
                push(sin(pop()));
                break;
            case EXP:
                op2 = exp(pop());
                if (op2 != HUGE_VAL && op2 != -HUGE_VAL && errno != ERANGE)
                    push(op2);
                else
                    printf("range error: result is out of range: %g\n", op2), errno = 0;
                break;
            case POW:
                op2 = pop();
                op2 = pow(op2, pop());
                if (errno == EDOM)
                    printf("domain error: see domain of pow function\n"), errno = 0;
                else if (errno == ERANGE && (op2 == HUGE_VAL || op2 == -HUGE_VAL))
                    printf("range error: result is out of range: %g\n", op2), errno = 0;
                else
                    push(op2);
                break;
            case PRINT:
                printf("\t%.8g\n", top());
                break;
            case DUPL:
                push(top());
                break;
            case SWAP:
                swap();
                break;
            case CLEAR:
                clear();
                break;
            case '\n':
                printf("\t%.8g\n", var['r' - 'a'] = pop());
                break;
            default:
                printf("error: unknown command %s\n", s);
                break;
        }

    }
    return 0;
}

