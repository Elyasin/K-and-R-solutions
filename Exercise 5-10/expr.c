#include <stdio.h>
#include <stdlib.h>   /* for atof() */

#define MAXOP   100   /* max size of operand or operator */
#define NUMBER  '0'   /* signal that a number was found */

int getop(char []);
void push(double);
double pop(void);

/* reverse Polish calculator */
int main(int argc, char *argv[]) {
    int type, i;
    double op2;
    char s[MAXOP];

    if (argc == 1)
        return 0;

    i = 1;
    while (argv[i] != NULL) {

        type = getop(argv[i]);

        switch (type) {
            case NUMBER:
                push(atof(argv[i]));
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
            default:
                printf("error: unknown command %s\n", s);
                break;
        }
        i++;
    }

    printf("\t%.8g\n", pop());

    return 0;
}

#define MAXVAL  100   /* maximum depth of val stack */

int sp = 0; /* next free stack position */
double val[MAXVAL]; /* value stack */

/* push:  push f onto value stack */
void push(double f) {
    if (sp < MAXVAL)
        val[sp++] = f;
    else
        printf("error: stack full, can't push %g\n", f);
}

/* pop:  pop and return top value from stack */
double pop(void) {
    if (sp > 0)
        return val[--sp];
    else {
        printf("error: stack empty\n");
        return 0.0;
    }
}

/* getop:  get next operator or numeric operand */
int getop(char s[]) {
    if (isdigit(s[0]) || (s[0] == '-' && s[1] != '\0'))
        /* number */
        return NUMBER;
    else
        /* not a number */
        return s[0];
}
