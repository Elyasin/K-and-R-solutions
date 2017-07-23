/* 
 * Exercise 1-20
 * Write a program detab that replaces tabs in the input with the proper number 
 * of blanks to space to the next tab stop. Assume a fixed set of tab stops, say 
 * every n columns. Should n be a variable or a symbolic parameter?
 * 
 */

#include <stdio.h>

#define MAXLINE 1000

#define TABSTOP 8   //change this to your system's tabstop size

int get_line(char line[], int maxline);
void detab(char to[], char from[]);

main() {
    int len;
    char line[MAXLINE];
    char detabbed_line[MAXLINE];

    while ((len = get_line(line, MAXLINE)) > 0) {
        detab(detabbed_line, line);
        printf("%s", detabbed_line);
    }
    return 0;
}

int get_line(char s[], int lim) {
    int c, i;

    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
        s[i] = c;
    if (c == '\n') s[i++] = c;
    s[i] = '\0';
    return i;
}

void detab(char to[], char from[]) {
    int c, i, j, k, spaces;

    for (i = 0, k = 0; (c = from[i]) != EOF && c != '\n'; ++i, ++k) {
        if (c == '\t') {
            spaces = TABSTOP - k % TABSTOP;
            for (j = 1; j <= spaces; ++j) {
                to[k++] = ' ';
            }
            --k;
        } else
            to[k] = c;
    }
    if (c == '\n') 
        to[k++] = c;
    to[k] = '\0';
}
