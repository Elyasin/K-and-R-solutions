#include <stdio.h>

void strcat2(char s[], char t[]);

int main(int argc, char** argv) {

    char s[100] = "This is the first sentence.";
    char t[] = "This is the second sentence.";

    strcat2(s, " ");
    strcat2(s, t);
    printf("%s\n", s);

    return 0;
}

/* strcat: concatenate t to end of s; s must be long enough */
void strcat2(char s[], char t[]) {

    while (*s) /* find end of s */
        s++;
    while (*s++ = *t++) /* copy t */
        ;

}
