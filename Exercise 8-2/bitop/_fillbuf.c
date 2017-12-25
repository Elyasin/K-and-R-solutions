#include "syscall.h"

FILE _iob[OPEN_MAX] = {/* stdin, stdout, stderr: */
    { 0, (char *) 0, (char *) 0, _READ, 0},
    { 0, (char *) 0, (char *) 0, _WRITE, 1},
    { 0, (char *) 0, (char *) 0, _WRITE | _UNBUF, 2}
};

#include <fcntl.h>

#define PERMS 0666  /* RW for owner, group, other */

long int lseek(int fd, long int offset, int whence);

/* fopen: open file, return file ptr */
FILE* fopen(char* name, char* mode) {

    int fd;
    FILE *fp;

    if (*mode != 'r' && *mode != 'w' && *mode != 'a')
        return NULL;

    for (fp = _iob; fp < _iob + OPEN_MAX; fp++)
        if ((fp->flag & (_READ | _WRITE)) == 0)
            break; /* found free slot */

    if (fp >= _iob + OPEN_MAX) /* no free slots */
        return NULL;

    if ((*mode == 'w'))
        fd = creat(name, PERMS);
    else if ((*mode == 'a')) {
        if ((fd = open(name, O_WRONLY, 0)) == -1)
            fd = creat(name, PERMS);
        lseek(fd, 0L, 2);
    } else
        fd = open(name, O_RDONLY, 0);

    if (fd == -1) /* couldn't access name */
        return NULL;

    fp->fd = fd;
    fp->cnt = 0;
    fp->base = NULL;
    fp->flag = (*mode == 'r') ? _READ : _WRITE;

    return fp;
}

void *malloc (long unsigned int size);
long int read (int fd, void *buf, long unsigned int nbytes);

/* _fillbuf: allocate and fill input buffer */
int _fillbuf(FILE *fp) {

    int bufsize;

    if ((fp->flag & (_READ | _EOF | _ERR)) != _READ)
        return EOF;

    bufsize = (fp->flag & _UNBUF) ? 1 : BUFSIZ;

    if (fp->base == NULL) /* no buffer yet */
        if ((fp->base = (char*) malloc(bufsize)) == NULL)
            return EOF; /* can't get buffer */

    fp->ptr = fp->base;

    fp->cnt = read(fp->fd, fp->ptr, bufsize);

    if (--fp->cnt < 0) {
        if (fp->cnt == -1)
            fp->flag |= _EOF;
        else
            fp->flag |= _ERR;
        fp->cnt = 0;
        return EOF;
    }

    return (unsigned char) *fp->ptr++;

}

long int write(int fd, void *bf, long unsigned int nbytes);

int main(int argc, char *argv[]) {
    FILE *fp;
    char c;
    if ( (fp = fopen("lorem_ipsum.txt", "r")) == NULL )
        return 1;
    else {
        while ( (c = getc(fp)) != EOF)
            write(1, &c, 1);
    }
    return 0;
}
