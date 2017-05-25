/* 
 * Exercise 1-17
 * Write a program to print all input lines that are longer than 80 characters.
 */

#include <stdio.h>
#define MAXLINE 1000

#define MAX 80

int get_line(char line[], int maxline);
void copy(char to[], char from[]);

main() {
    int len;
    char line[MAXLINE];

    while ((len = get_line(line, MAXLINE)) > 0)
        if (len > MAX)
            printf("%s", line);
    
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

void copy(char to[], char from[]) {
    int i;

    i = 0;
    while ((to[i] = from[i]) != '\0')
        ++i;
}
