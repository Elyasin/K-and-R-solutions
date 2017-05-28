 #include <stdio.h>

int lower(char c);

int main(int argc, char** argv) {

    char c;

    c = lower('A');
    printf("%c\n", c);

    c = lower('b');
    printf("%c\n", c);

    return 0;
}

int lower(char c) {
    return (c >= 'A' && c <= 'Z') ? (c + 'a' - 'A') : c;
}
