#include <stdio.h>

#define MAXLINE 1000

int any(char s1[], char s2[]);

int main(int argc, char** argv) {

    char s1[MAXLINE] = "This is a test.";
    char s_ok[] = "b.ac";
    char s_ko[] = "yxz";
    char s_empty[] = "";
    int pos;

    pos = any(s1, s_ok);
    if (pos == -1)
        printf("Nothing found\n");
    else
        printf("Found at position %d\n", pos);

    pos = any(s1, s_ko);
    if (pos == -1)
        printf("Nothing found\n");
    else
        printf("Found at position %d\n", pos);

    pos = any(s1, s_empty);
    if (pos == -1)
        printf("Nothing found\n");
    else
        printf("Found at position %d\n", pos);

    return 0;
}

int any(char s1[], char s2[]) {

    int i, j;

    for (i = 0; s1[i] != '\0'; i++)
        for (j = 0; s2[j] != '\0'; j++)
            if (s1[i] == s2[j])
                return i;

    return -1;
}
