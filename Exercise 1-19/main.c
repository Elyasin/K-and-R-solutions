/* 
 * Exercise 1-19
 * Write a function reverse(s) that reverses the character string s. Use it to 
 * write a program that reverses its input a line at a time.
 * 
 */

#include <stdio.h>
#define MAXLINE 1000

int get_line(char line[], int maxline);
void reverse(char s[]);

main() {
    int len;
    char line[MAXLINE];

    while ((len = get_line(line, MAXLINE)) > 0) {
        reverse(line);
        printf("%s", line);
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

/* s must end with newline character */
void reverse(char s[]) {
    char c;
    int length = 0;
    int i;

    for (i = 0; s[i] != '\n'; i++)
        length++;

    for (i = 0; i < length / 2; i++) {
        c = s[length - i - 1];
        s[length - i - 1] = s[i];
        s[i] = c;
    }
}