#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXTOKEN 100

enum {
    NAME, PARENS, BRACKETS, ERROR
};

void dcl(void);
void dirdcl(void);

int gettoken(void);
int tokentype; // type of last token
char token[MAXTOKEN]; // last token string
char name[MAXTOKEN]; // identifier name
char datatype[MAXTOKEN]; // datatype: char, int, short, long, float, double, void
char out[1000]; // output string

main() {

    while (gettoken() != EOF) {
        strcpy(datatype, token);
        if (!is_valid_datatype(datatype)) {
            printf("error: datatype unknown %s\n", datatype);
            while (gettoken() != '\n')
                ;
        } else {
            out[0] = '\0';
            dcl();
            if (tokentype != '\n') {
                printf("syntax error: %c\n", tokentype);
                while (gettoken() != '\n')
                    ;
            } else
                printf("%s %s %s\n", name, out, datatype);
        }
    }
    return 0;
}

void dcl(void) {

    int ns;

    for (ns = 0; gettoken() == '*';)
        ns++;
    dirdcl();
    while (ns-- > 0)
        strcat(out, " pointer to");
}

void dirdcl(void) {

    int type;

    if (tokentype == '(') {
        dcl();
        if (tokentype != ')')
            printf("error: missing )\n");
    } else if (tokentype == NAME)
        strcpy(name, token);
    else
        printf("error: expected name or (dcl)\n");

    while ((type = gettoken()) == PARENS || type == BRACKETS)
        if (type == PARENS)
            strcat(out, " function returning");
        else {
            strcat(out, " array");
            strcat(out, token);
            strcat(out, " of");
        }
}

int gettoken(void) {

    int c, getch(void);
    void ungetch(int);
    char *p = token;

    while ((c = getch()) == ' ' || c == '\t')
        ;
    if (c == '(') {

        // consume blanks after opening parenthesis
        while ((c = getch()) == ' ' || c == '\t')
            ;

        if (c == ')') {
            strcpy(token, "()");
            return tokentype = PARENS;
        } else {
            ungetch(c);
            return tokentype = '(';
        }
    } else if (c == '[') {

        // consume blanks after opening bracket
        while ((c = getch()) == ' ' || c == '\t')
            ;
        ungetch(c);

        for (*p++ = '['; (*p++ = getch()) != ']';)
            ;
        *p = '\0';
        return tokentype = BRACKETS;
    } else if (isalpha(c)) {
        for (*p++ = c; isalnum(c = getch());)
            *p++ = c;
        *p = '\0';
        ungetch(c);
        return tokentype = NAME;
    } else
        return tokentype = c;
}

int is_valid_datatype(char *datatype) {
    return strcmp(datatype, "char") == 0 || 
            strcmp(datatype, "short") == 0 ||
            strcmp(datatype, "int") == 0 || 
            strcmp(datatype, "long") == 0 ||
            strcmp(datatype, "float") == 0 ||
            strcmp(datatype, "double") == 0 ||
            strcmp(datatype, "void") == 0;
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
