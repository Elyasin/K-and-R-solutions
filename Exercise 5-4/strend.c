#include <stdio.h>

int strend(char s[], char t[]);

int main(int argc, char** argv) {

    char s[] = "This is a test.";
    char t[] = "a test";
    char u[] = "a test.";
    char v[] = "This is";

    printf("S[] = %s\n", s);
    printf("t[] = %s\n", t);
    printf("u[] = %s\n", u);
    printf("v[] = %s\n", v);

    int ret = strend(s, t);
    printf("t sub string at end of s? %d\n", ret);
    ret = strend(s, u);
    printf("u sub string at end of s? %d\n", ret);
    ret = strend(s, v);
    printf("v sub string at end of s? %d\n", ret);

    return 0;
}

int strend(char s[], char t[]) {

    for (; *s; s++) {
        if (*s == *t) {
            char *s1 = s;
            char *t1 = t;
            while (*s1 == *t1 && *s1 != '\0')
               s1++, t1++; 
            /* The C Programming Language, page 245
             * "There is one exception: The address of the first element of the
             * past the end element can be used in pointer arithmetic."
             */
            if (*s1 == '\0' && *t1 == '\0')
                return 1;
        }
    }
    return 0;
}
