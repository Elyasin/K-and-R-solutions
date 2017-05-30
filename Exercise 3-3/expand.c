#include <stdio.h>

#define MAXLINE 1000

void expand(char s1[], char s2[]);

int main(int argc, char** argv) {

    char s1[MAXLINE] = "This is a simple test for -a-z (leading minus) and\n0-9-(trailing minus) and\na-n-z or\nsimpler a-b-c\nor even a-z0-9.\n";
    char s2[MAXLINE];

    printf("%s\n", s1);
    expand(s1, s2);
    printf("%s\n", s2);

    return 0;
}

void expand(char s1[], char s2[]) {

    int i, j, k, start, end;

    for (i = 0, j = 0; s1[i] != '\0'; i++) {
        if (s1[i] == '-' && isalnum(s1[i - 1]) && isalnum(s1[i + 1])) {
            start = s1[i - 1], end = s1[++i];
            for (k = start + 1; k <= end; k++)
                s2[j++] = k;
        } else
            s2[j++] = s1[i];
    }

    s2[j] = '\0';
}
