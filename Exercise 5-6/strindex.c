#include <stdio.h>

#define MAXLINE 1000    /* maximum input line length */

int get_line(char line[], int max);
int strindex(char source[], char searchfor[]);

char pattern[] = "ould";
/* pattern to search for */

/* find all lines matching pattern */
main() {
    char line[MAXLINE];
    int found = 0;

    while (get_line(line, MAXLINE) > 0)
        if (strindex(line, pattern) >= 0) {
            printf("%s", line);
            found++;
        }
    return found;
}

/* getline:  get line into s, return length */
int get_line(char s[], int lim) {
    int c;
    char *p;

    p = s;
    while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
        *s++ = c;
    if (c == '\n')
        *s++ = c;
    *s = '\0';
    return s - p;
}

/* strindex:  return index of t in s, −1 if none */
int strindex(char s[], char t[]) {
    char *p, *q, *r;

    for (p = s; *s; s++) {
        for (q = s, r = t; *t != '\0' && *q == *t; q++, t++)
            ;
        if ((t - r) > 0 && *t == '\0')
            return s - p;

    }
    return -1;
}
