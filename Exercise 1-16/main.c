/* 
 * Exercise 1-16
 * Revise the main routine of the longest-line program so it will correctly 
 * print the length of arbitrarily long input lines, and as much as possible 
 * of the text.
 * 
*/

#include <stdio.h>
#define MAXLINE 1000

int get_line(char line[], int maxline);
void copy(char to[], char from[]);

main() {
    int len, temp_len = 0;
    int max;
    int overflow = 0;
    char line[MAXLINE];
    char longest[MAXLINE];
    char temp_line[MAXLINE];

    max = 0;
    while ((len = get_line(line, MAXLINE)) > 0) {
        if (len < MAXLINE - 1 || line[len - 1] == '\n') {
            if (overflow == 0) {
                if (len > max) {
                    max = len;
                    copy(longest, line);
                }
            } else {
                temp_len += len;
                if (temp_len > max) {
                    max = temp_len;
                    copy(longest, temp_line);

                }
            }
            temp_len = 0;
            overflow = 0;
        } else {
            if (temp_len == 0) copy(temp_line, line);
            temp_len += len;
            overflow = 1;
        }

    }
    if (max > 0) {
        printf("\nMax length: %d\nText: %s\n", max, longest);
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

void copy(char to[], char from[]) {
    int i;

    i = 0;
    while ((to[i] = from[i]) != '\0')
        ++i;
}
