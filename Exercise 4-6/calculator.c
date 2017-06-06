#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <errno.h>

#define MAXOP 100 /* max size of operand or operator */
#define NUMBER  '0' /* signal that a number was found */
#define SINUS   '~'
#define EXP     '\"'
#define POW     '^'
#define PRINT   '?'
#define DUPL    ':'
#define SWAP    '#'
#define CLEAR   '_'
#define SET_VAR '8' // capital characters set values
#define GET_VAR '9' // small characters read values

#define ALPHA   26

int getop(char []);
void push(double);
double pop(void);
double top(void);
void swap(void);
void clear(void);

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

#include <ctype.h>

int getch(void);
void ungetch(int);

/* getop:  get next operator or numeric operand */
int getop(char s[]) {
    int i, c;

    while ((s[0] = c = getch()) == ' ' || c == '\t')
        ;
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
                ungetch(c);
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
        ungetch(c);

    return NUMBER;
}

#define BUFSIZE 100

char buf[BUFSIZE]; /* buffer for ungetch */
int bufp = 0; /* next free position in buf */

int getch(void) /* get a (possibly pushed back) character */ {
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) /* push character back on input */ {
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}
