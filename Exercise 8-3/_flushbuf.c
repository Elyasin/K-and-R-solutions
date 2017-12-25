#include "syscall.h"

FILE _iob[OPEN_MAX] = {/* stdin, stdout, stderr: */
    { 0, (char *) 0, (char *) 0, _READ, 0},
    { 0, (char *) 0, (char *) 0, _WRITE, 1},
    { 0, (char *) 0, (char *) 0, _WRITE | _UNBUF, 2}
};

#include <fcntl.h>

#define PERMS 0666  /* RW for owner, group, other */

long int lseek(int, long int, int);

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

void *malloc (long unsigned int);
long int read (int, void *, long unsigned int);

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

long int write(int, void *, long unsigned int);

/* _flushbuf: allocate and flush output buffer */
int _flushbuf(int c, FILE *fp) {

    int bufsize;

    if ((fp->flag & (_WRITE | _ERR)) != _WRITE)
        return EOF;

    bufsize = (fp->flag & _UNBUF) ? 1 : BUFSIZ;

    if (fp->base == NULL) { /* no buffer yet */
        if ((fp->base = (char*) malloc(bufsize)) == NULL)
            return EOF; /* can't get buffer */
    } else {
        unsigned nchar = fp->ptr - fp->base;
        if ( (write(fp->fd, fp->base, nchar) != nchar) ) {
            fp->flag |= _ERR;
            return EOF;
        }
    }
    fp->ptr = fp->base;
    *fp->ptr++ = (char) c;
    fp->cnt = bufsize - 1;
    return c;
}

/* fflush: flush file buffer */
int fflush(FILE *fp) {
    if ( (fp->flag & _WRITE) != _WRITE) {
        fp->flag |= _ERR;
        write(2, "Error at fflush 1\n", 18);
        return EOF;
    }
    if ( _flushbuf('0', fp) == EOF ) {
        write(2, "Error at fflush 2\n", 18);
        return EOF;
    }
    fp->ptr = fp->base;
    fp->cnt = (fp->flag & _UNBUF) ? 1 : BUFSIZ;
    return 0;
}

void free (void *);
int close(int);

/* fclose: close file */
int fclose(FILE *fp) {
    if ( fflush(fp) == EOF )
        return EOF;
    free(fp->base);
    fp->base = fp->ptr = NULL;
    fp->cnt = 0;
    close(fp->fd);
    return 0;
}

int main(int argc, char *argv[]) {
    FILE *fpin, *fpout;
    char c;
    if ( (fpin = fopen("lorem_ipsum.txt", "r")) == NULL )
        return 1;
    if ( (fpout = fopen("result.txt", "w")) == NULL )
        return 1;
    while ( (c = getc(fpin)) != EOF )
        putc(c, fpout);
    fclose(fpout);
    return 0;
}
