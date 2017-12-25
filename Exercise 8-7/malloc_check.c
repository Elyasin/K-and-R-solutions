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

void Free(void *);
void *Malloc(unsigned);

int main(int argc, char *argv[]) {

    int r = 36;
    int *p = (int *) Malloc(sizeof(int));    
    *p = 36;
    if (r != *p)
        return 1;
    Free(p);

    void *q = Malloc(1024*1024+1);
    if (q == NULL)
        return 1;

    return 0;
}



static unsigned max_allocated = 0;  /* largest allocated size */
static Header base;             /* empty list to get started */
static Header *freep = NULL;    /* start of free list */

static Header *Morecore(unsigned);

#define MAXALLOC (1024*1024)

/* Malloc: general-purpose storage allocator */
/* user can ask for maximum of 1024*1024 bytes in one call */
void *Malloc(unsigned nbytes) {

    Header *p, *prevp;
    Header *Morecore(unsigned);
    unsigned nunits;

    nunits = (nbytes + sizeof(Header) - 1) / sizeof(Header) + 1;

    if (nbytes > MAXALLOC)
        return NULL;
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



#define NALLOC 1024 /* minimum #units to request */

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
    max_allocated = (up->s.size > max_allocated) ? up->s.size : max_allocated;
    Free((void *)(up + 1));
    return freep;
}



/* free: put block ap in free list */
void Free(void *ap) {
    
    Header *bp, *p;

    bp = (Header *)ap - 1;  /* point to block header */
    if ( (bp->s.size <= 0) && (bp->s.size >= max_allocated) )
        return;
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
