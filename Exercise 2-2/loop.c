#include <stdio.h>

#define MAXLINE 1000

int get_line(char s[], int lim);

int main(int argc, char** argv) {

    char s[MAXLINE];
    get_line(s, MAXLINE);
    printf("%s", s);

    return 0;
}

int get_line(char s[], int lim) {
    int c, i, LOOP;

    i = 0;
    LOOP = 1;
    while ( LOOP ) {
        if (i >= lim-1)
            LOOP = 0;
        else if ((c = getchar()) == EOF)
            LOOP = 0;
        else if (c == '\n')
            LOOP = 0;
        else {
            s[i] = c;
            i++;
        }
    }

    if (c == '\n') {
        s[i] = c;
        ++i;
    }
    s[i] = '\0';
    return i;
}
