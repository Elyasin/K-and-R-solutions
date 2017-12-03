#include <stdio.h>
#include <stdlib.h>

#define MAXOP 100 /* max size of operand or operator */

int getop(char[]);
void push(double);
double pop(void);
double top(void);

/*
 * scanf is used to read a string until EOF is returned.
 * The string is scanned with sscanf. First to see if the string
 * represents a number. If the string is not a number then sscanf is used
 * to see if it is an operator.
 * The result is not automatically printed when a newline is read. Instead the
 * user has to type p to print the result from the stack.
 * The function top is used to retrieve the top of the stack.
 */

/* reverse Polish calculator */
main() {
    double op1, op2;
    char s[MAXOP], c;

    while (scanf("%s", s) != EOF) {
        if (sscanf(s, "%lf", &op1) == 1) {
            push(op1);
        } else if (sscanf(s, "%c", &c) == 1) {
            switch (c) {
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
                case 'p':
                    printf("\t%.8g\n", top());
                    break;
                default:
                    printf("error: unknown command %s\n", s);
                    break;
            }
        }
    }

    return 0;
}


#define MAXVAL  100   /* maximum depth of val stack */

int sp = 0;
/* next free stack position */
double val[MAXVAL];
/* value stack */

/* push:  push f onto value stack */
void push(double f) {
    if (sp < MAXVAL)
        val[sp++] = f;
    else
        printf("error: stack full, can′t push %g\n", f);

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

/* top: return top value from stack */
double top(void) {
    if (sp > 0)
        return val[sp - 1];
    else {
        printf("error: stack empty\n");
        return 0.0;
    }
}
