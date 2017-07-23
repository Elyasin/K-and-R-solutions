#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXTOKEN 100

enum {
    NAME, PARENS, BRACKETS, ERROR
};

enum {
    NO, YES
};

void dcl(void);
void dirdcl(void);

int gettoken(void);
int next_token(void);

int tokentype; // type of last token
char token[MAXTOKEN]; // last token string
char name[MAXTOKEN]; // identifier name
char datatype[MAXTOKEN]; // datatype: char, int, short, long, float, double, void
char out[1000]; // output string

int prev_token = NO;

main() {

    int type;
    char temp[MAXTOKEN];

    while (gettoken() != EOF) {
        strcpy(out, token);
        while ((type = gettoken()) != '\n') {
            if (type == PARENS || type == BRACKETS)
                strcat(out, token);
            else if (type == '*') {
                if ( (type = next_token()) != PARENS && type != BRACKETS)
                    sprintf(temp, "*%s", out);
                else
                    sprintf(temp, "(*%s)", out);
                strcpy(out, temp);
            } else if (type == NAME) {
                sprintf(temp, "%s %s", token, out);
                strcpy(out, temp);
            } else
                printf("invalid input at %s\n", token);
        }
        printf("%s\n", out);
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

int next_token(void) {

    int type;
    prev_token;

    type = gettoken();
    prev_token = YES;
    return type;
}

int gettoken(void) {

    int c, getch(void);
    void ungetch(int);
    char *p = token;

    if (prev_token == YES) {
        prev_token = NO;
        return tokentype;
    }

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
    return strcmp(datatype, "char") != 0 &&
            strcmp(datatype, "short") != 0 &&
            strcmp(datatype, "int") != 0 &&
            strcmp(datatype, "long") != 0 &&
            strcmp(datatype, "float") != 0 &&
            strcmp(datatype, "double") != 0 &&
            strcmp(datatype, "void") != 0;
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
