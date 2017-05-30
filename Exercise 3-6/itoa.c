#include <stdio.h>

#define MAXLINE 100

void reverse(char s[]);
void itoa(int n, char s[], int p);

int main(int argc, char** argv) {

    char s[MAXLINE];
    int n = 26;

    itoa(n, s, 10);
    printf(":%s:\n", s);

    return 0;
}

void itoa(int n, char s[], int p) {

    int i, sign, count;

    sign = n;

    i = 0;
    count = 0;
    do {
        s[i++] = abs(n % 10) + '0';
        count++;
    } while (n /= 10);

    if (sign < 0)
        s[i++] = '-', count++;

    for (; count < p; count++)
        s[i++] = ' ';

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
