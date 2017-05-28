#include <stdio.h>

#define MAXLINE 1000

void squeeze(char s1[], char s2[]);

int main(int argc, char** argv) {

    char s1[MAXLINE] = "Tbhcids figs jak ltmesotp, qirsunv'wt xiytz?";
    char s2[] = "bcdfgjklmopqruvwxyz";

    squeeze(s1, s2);
    printf("%s\n", s1);

    return 0;
}

void squeeze(char s1[], char s2[]) {

    short bool = 0;
    int i, j, k;

    for (i = j = 0; s1[i] != '\0'; i++) {
        for (k = 0; s2[k] != '\0'; k++)
            if (s1[i] == s2[k]) {
                bool = 1;
                break;
            }
        if (bool == 0)
            s1[j++] = s1[i];
        bool = 0;
    }

    s1[j] = '\0';

}
