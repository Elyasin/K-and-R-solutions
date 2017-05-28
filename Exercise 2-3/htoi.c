#include <stdio.h>
#include <ctype.h>

int htoi(char s[]);

int main(int argc, char** argv) {

    int a = htoi("0x17F");
    printf("0x17F = %d\n", a);

    a = htoi("0Xf71");
    printf("0Xf71 = %d\n", a);

    a = htoi("fff");
    printf("fff = %d\n", a);

    a = htoi("ABC");
    printf("ABC = %d\n", a);

    return 0;
}

// a - 97
// f - 102
// 0 - 48
// 9 - 57
// A - 65
// F - 70

int htoi(char s[]) {
    int i, n;

    if (s[0] == '0' && (s[1] == 'x' || s[1] == 'X'))
        i = 2;
    else
        i = 0;

    n = 0;
    for (; isxdigit(s[i]); ++i) {
        if (isalpha(s[i]))
            n = 16 * n + (tolower(s[i]) - 'a' + 10); // don't digits 0-9
        else
            n = 16 * n + (s[i] - '0');

    }

    return n;
}
