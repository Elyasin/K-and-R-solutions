#include <stdio.h>
#include <string.h>

#define MAXLINE 1000

int getch(void);
void ungetch(int);
void ungets(char*);

main() {

    int i, c;
    char s[MAXLINE];
    char t[MAXLINE];

    i = 0;
    while ((s[i++] = getch()) != '\n')
        ;
    s[i] = '\0';

    printf("Reading: %s", s);
    ungets(s);
    printf("ungets called\n");
    i = 0;
    while ((t[i++] = getch()) != '\n')
        ;
    printf("Reading again: %s", s);

    return 0;
}


#define BUFSIZE 100

char buf[BUFSIZE]; /* buffer for ungets */
int bufp = 0; /* next free position in buf */

int getch(void) {
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) {
    if (bufp >= BUFSIZE) 
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}

void ungets(char s[]) {
    int len;

    len = strlen(s);

    for (;len > 0;)
        ungetch(s[--len]);
}

