#include <stdio.h>

#define MAXLINE 1000

#define TEXT    0
#define ESCAPE  1

char STATUS = TEXT;

void escape(char s[], char t[]);
void descape(char s[], char t[]);

int main(int argc, char** argv) {

    char t[MAXLINE] = "This is a small test.\n\tIt contains \"\'\\ escaped \n\t characters.\n";
    char s[MAXLINE] = "Before test";

    printf("%s\n", t);
    escape(s, t);
    printf("%s\n", s);
    descape(t, s);
    printf("%s\n", t);

    return 0;
}

void escape(char s[], char t[]) {

    int i, j;

    for (i = 0, j = 0; t[i] != '\0'; i++) {
        switch (t[i]) {
            case '\n':
                s[j++] = '\\';
                s[j++] = 'n';
                break;
            case '\t':
                s[j++] = '\\';
                s[j++] = 't';
                break;
            default:
                s[j++] = t[i];
                break;
        }
    }
    s[j] = '\0';
}

void descape(char s[], char t[]) {

    int i, j;

    for (i = 0, j = 0; t[i] != '\0'; i++) {
        switch (STATUS) {
            case TEXT:
                if (t[i] == '\\') STATUS = ESCAPE;
                else s[j++] = t[i];
                break;
            case ESCAPE:
                if (t[i] == 'n') s[j++] = '\n';
                else if (t[i] == 't') s[j++] = '\t';
                else s[j++] = t[--i];
                STATUS = TEXT;
                break;
        }
    }
    s[j] = '\0';
}
