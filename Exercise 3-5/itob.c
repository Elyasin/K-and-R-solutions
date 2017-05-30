#include <stdio.h>

#define MAXLINE 100

void reverse(char s[]);
void itob(int n, char s[], int b);

int main(int argc, char** argv) {

    char s[MAXLINE];
    int n = 26;
    printf("Number in decimal: %d\n", n);

    int b = 16;
    itob(n, s, b);
    printf("Number in base %d: %s\n", b, s);

    b = 2;
    itob(n, s, b);
    printf("Number in base %d: %s\n", b, s);

    return 0;
}

void itob(int n, char s[], int b) {

    int i, sign;

    sign = n;

    i = 0;
    do {
        char x = abs(n % b);
        if (x < 10)
            x = x + '0';
        else
            x = x - 10 + 'A';
        s[i++] = x;
    } while (n /= b);

    if (sign < 0)
        s[i++] = '-';

    s[i] = '\0';

    reverse(s);
}

void reverse(char s[]) {

    int i;
    int length = 0;

    for (i = 0; s[i] != '\0'; i++)
        length++;

    char temp[length];
    for (i = 0; i < length; i++)
        temp[i] = s[i];

    for (i = 0; i < length; i++)
        s[i] = temp[length - 1 - i];

}
