#include <stdio.h>
#include <string.h>

#define MAXLINE 1000

/* find: print lines that match pattern from 1st arg */
int main(int argc, char** argv) {

    FILE *fp;
    char *text;
    char line[MAXLINE];
    long lineno = 0;
    int c, except = 0, number = 0, found = 0;

    while (--argc > 0 && (*++argv)[0] == '-')
        while (c = *++argv[0])
            switch (c) {
                case 'x':
                    except = 1;
                    break;
                case 'n':
                    number = 1;
                    break;
                default:
                    printf("find: illegal option %c\n", c);
                    argc = 0;
                    found = -1;
            }

    if (argc <= 1)
        printf("Usage: find -x -n pattern [file1] [file2] [...]\n");
    else {
        text = *argv;
        while ((--argc > 0) && (fp = fopen(*++argv, "r")) != NULL) {
            lineno = 0;
            while (fgets(line, MAXLINE, fp) > 0) {
                lineno++;
                if ((strstr(line, text) != NULL) != except) {
                    if (number)
                        printf("%ld:", lineno);
                    printf("%s: %s", *argv, line);
                    found++;
                }
            }
            if (ferror(fp))
                fprintf(stderr, "%s: file error\n", *argv);
            fclose(fp);
        }
    }



    return found;
}

