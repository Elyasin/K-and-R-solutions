#include <stdio.h>

#define MAXLINE 1000

int get_line(char line[], int max);
int strindex(char source[], char searchfor[]);
int strrindex(char source[], char searchfor[]);

char pattern[] = "ould";

int main(int argc, char** argv) {

    char line[MAXLINE];
    int found = 0;
    int pos;

    while (get_line(line, MAXLINE) > 0)
        if ((pos = strrindex(line, pattern)) >= 0) {
            printf("Position: %d\n", pos);
            printf("%s", line);
            found++;
        }

    return found;
}

int get_line(char s[], int lim) {

    int c, i;

    i = 0;
    while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
        s[i++] = c;
    if (c == '\n')
        s[i++] = c;
    s[i] = '\0';

    return i;
}

int strindex(char s[], char t[]) {

    int i, j, k;

    for (i = 0; s[i] != '\0'; i++) {
        for (j = i, k = 0; t[k] != '\0' && s[j] == t[k]; j++, k++)
            ;
        if (k > 0 && t[k] == '\0')
            return i;
    }

    return -1;
}

int strrindex(char s[], char t[]) {

    int i, j, k, length;

    length = 0;
    while (s[length++] != '\0')
        ;

    for (i = length - 1; i >= 0; i--) {
        for (j = i, k = 0; t[k] != '\0' && s[j] == t[k]; j++, k++)
            ;
        if (k > 0 && t[k] == '\0')
            return i;
    }

    return -1;
}
