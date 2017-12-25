#define NULL 0


typedef long Align;     /* for alignment to long boundary */

union header {          /* block header */
    struct {
        union header *ptr;  /* next block if on free list */
        unsigned size;      /* size of this block */
    } s;
    Align x;            /* force alignment of blocks */
};

typedef union header Header;



static Header base;            /* empty list to get started */
static Header *freep = NULL;    /* start of free list */

void Free(void *);
void *Malloc(unsigned);
void *Calloc(unsigned, unsigned);

int main(int argc, char *argv[]) {

    int r = 36;
    int *p = (int *) Malloc(sizeof(int));    
    *p = 36;
    if (r != *p) 
        return 1;
    Free(p);

    int *arr = (int *) Calloc(10, sizeof(int));
    int i;
    for (i=0; i<10; i++)
        arr[i] = i+1;

    return ((arr[0] == 1) && (arr[9] == 10)) ? 0 : 1;

}


static Header *Morecore(unsigned);

/* Malloc: general-purpose storage allocator */
void *Malloc(unsigned nbytes) {

    Header *p, *prevp;
    Header *Morecore(unsigned);
    unsigned nunits;

    nunits = (nbytes + sizeof(Header) - 1) / sizeof(Header) + 1;
    if ((prevp = freep) == NULL) {  /* no free list yet */
        base.s.ptr = freep = prevp = &base;
        base.s.size = 0;
    }
    for (p = prevp->s.ptr; ; prevp = p, p = p->s.ptr) {
        if (p->s.size >= nunits) {  /* big enough */
            if (p->s.size == nunits)    /* exactly */
                prevp->s.ptr = p->s.ptr;
            else {  /* allocate tail end */
                p->s.size -= nunits;
                p += p->s.size;
                p->s.size = nunits;
            }
            freep = prevp;
            return (void *)(p + 1);
        }
        if (p == freep) /* wrapped around free list */
            if ( (p = Morecore(nunits)) == NULL )
                return NULL;    /* none left */
    }
}


void *Calloc(unsigned n, unsigned size) {

    unsigned len = n * size;
    char *p = Malloc(len);
    if (p == NULL)
        return NULL;

    char *q = p;
    int i;
    for (i=0; i<len; i++)
        *q++ = 0;

    return p;
}


#define NALLOC 1024 /* minimum units to request */

/* Morecore: ask system for more memory */
static Header *Morecore(unsigned nu) {

    char *cp, *sbrk(int);
    Header *up;

    if (nu < NALLOC)
        nu = NALLOC;
    cp = sbrk(nu * sizeof(Header));
    if (cp == (char *) -1)  /* no space at all */
        return NULL;
    up = (Header *) cp;
    up->s.size = nu;
    Free((void *)(up + 1));
    return freep;
}



/* free: put block ap in free list */
void Free(void *ap) {
    
    Header *bp, *p;

    bp = (Header *)ap - 1;  /* point to block header */
    for (p = freep; !(bp > p && bp < p->s.ptr); p = p->s.ptr)
        break;  /* freed block at start or end of arena */

    if (bp + bp->s.size == p->s.ptr) {  /* join to upper nbr */
        bp->s.size += p->s.ptr->s.size;
        bp->s.ptr = p->s.ptr->s.ptr;
    } else
        bp->s.ptr = p->s.ptr;
    if (p + p->s.size == bp) {
        p->s.size += bp->s.size;
        p->s.ptr = bp->s.ptr;
    } else
        p->s.ptr = bp;
    freep = p;
}
