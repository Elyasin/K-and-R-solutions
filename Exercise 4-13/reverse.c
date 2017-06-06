#include <stdio.h>
#include <string.h>

void reverse(char s[]);

int main(int argc, char** argv) {

    char s[] = ".esrever rof tset elpmis a si sihT";
    char t[] = "KO";

    printf("Reversing '%s': ", s);
    reverse(s);
    printf("%s\n", s);
    printf("Reversing '%s': ", t);
    reverse(t);
    printf("%s\n", t);

    return 0;
}

void reverse(char s[]) {

    char c1, c2;
    int len = strlen(s);

    if (len < 2)
        return;

    c1 = s[0];
    c2 = s[len - 1];
    s[len - 1] = '\0';
    reverse(s + 1);
    s[0] = c2;
    s[len - 1] = c1;

}
