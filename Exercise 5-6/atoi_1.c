#include <stdio.h>

int a_to_i(char s[]);

int main(int argc, char** argv) {

    int n;
    char s[] = "123456789";

    n = a_to_i(s);
    printf("%d\n", n);

    return 0;
}

/* atoi:  convert s to integer */
int a_to_i(char s[]) {

    int n = 0;
    
    for (; *s >= '0' && *s <= '9'; ++s)
        n = 10 * n + (*s - '0');
    return n;
}
