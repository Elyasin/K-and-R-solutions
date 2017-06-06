#include <stdio.h>
#include <string.h>

#define MAXLINE 20

void itoa(int n, char s[]);

int main(int argc, char** argv) {

    int n;
    char s[MAXLINE];

    n = -2147483648;
    itoa(n, s);
    printf("%s\n", s);
    n = 2147483647;
    itoa(n, s);
    printf("%s\n", s);

    return 0;
}


void itoa(int n, char s[]) {

    int static i = 0;

    if (n / 10) 
        itoa(n / 10, s);
    else { 
        i = 0;
        if (n < 0)
            s[i++] = '-'; 
    }
   
    s[i++] = abs(n % 10) + '0';
    s[i] = '\0';
}
