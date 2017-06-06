#include <stdio.h>
#include "calc.h"

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
    if (sp > 0) {
        return val[sp - 1];
    } else {
        printf("error: stack empty\n");
        return 0.0;
    }
}

/* swap two top values */
void swap(void) {
    if (sp > 1) {
        double t1 = pop();
        double t2 = pop();
        push(t1);
        push(t2);
    } else
        printf("error: stack empty or not enough values\n");
}

/* clear the stack */
void clear(void) {
    sp = 0;
}
