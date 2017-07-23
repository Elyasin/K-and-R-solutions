#include <stdio.h>

void reverse(char s[]);

int main(int argc, char** argv) {

    char s[] = "This is a simple test for reverse.";

    reverse(s);
    printf("%s\n", s);
    reverse(s);
    printf("%s\n", s);

    return 0;
}

#include <string.h>

void reverse(char s[]) {

    char c1, c2;
    int len = strlen(s);

    if (len < 2)
        return;

    c1 = *s;
    c2 = *(s + len - 1);
    *(s + len - 1) = '\0';
    reverse(s + 1);
    *s = c2;
    *(s + len - 1) = c1;

}

