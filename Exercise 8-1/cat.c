#include <fcntl.h>
#include "syscall.h"
#include <stdio.h>

void error(char *fmt, ...);

/* cat: concatenate file */
int main(int argc, char** argv) {

    int fd;
    void filecopy(int, int);
    char *prog = argv[0]; /* program name for errors */

    if (argc == 1)
        filecopy(0, 1);
    else
        while (--argc > 0)
            if ((fd = open(*++argv, O_RDONLY, 0)) == -1)
                error("%s: can't open %s\n", prog, *argv);
            else {
                filecopy(fd, 1);
                close(fd);
            }

    return 0;
}

/* filecopy: copy file ifp to file ofp */
void filecopy(int fdin, int fdout) {
    char buf[BUFSIZ];
    int n;

    while ((n = read(fdin, buf, BUFSIZ)) > 0)
        write(fdout, buf, n);

}
