typedef long Align; /* для выравнивания по границе long */
union header { /* заголовок блока: */
    struct {
        union header *ptr; /* след. блок в списке свободных */
        unsigned size; /* размер этого блока */
    } s;
    Align x; /* принудительное выравнивание блока */
};
typedef union header Header;

static Header base; /* пустой список для нач. запуска */
static Header *freep = NULL; /* начало в списке своб. блоков */
/* malloc: универсальный распределитель памяти */
void *malloc(unsigned nbytes)
{
    Header *p, *prevp;
    Header *morecore(unsigned);
    unsigned nunits;
    nunits = (nbytes + sizeof (Header) - 1) / sizeof (Header) + 1;
    if ((prevp = freep) == NULL) { /* списка своб. памяти еще нет */
        base.s.ptr = freep = prevp = &base;
        base.s.size = 0;
    }
    for (p = prevp->s.ptr; ; prevp = p, p = p->s.ptr) {
        if (p->s.size >= nunits) { /* достаточно большой */
            if (p->s.size == nunits) /* точно нужного размера */
                 prevp->s.ptr = p->s.ptr;
            else { /* отрезаем хвостовую часть */
                p->s.size -= nunits;
                p += p->s.size;
                p->s.size = nunits;
            }
            freep = prevp;
            return (void *)(p+1);
        }
        if (p == freep) /* прошли полный цикл по списку */
            if ((p = morecore(nunits)) == NULL)
                return NULL; /* больше памяти нет */
    }
}

#define NALLOC 1024 /* миним. число единиц памяти для запроса */
/* morecore: запрашивает у системы дополнительную память */
static Header * morecore( unsigned nu)
{
    char *cp, *sbrk(int);
    Header *up;
    if (nu < NALLOC)
        nu = NALLOC;
        ср = sbrk(nu * sizeof(Header));
    if (cp == (char *) -1) /* больше памяти нет */
        return NULL;
    up = (Header *) cp;
    up->s.size = nu;
    free((void *)(up+1));
    return freep; // ?
}

/* free: включает блок в список свободной памяти */
void free(void *ap)
{
    Header *bp, *p;
    bp = (Header *)ap -1; /* указатель на заголовок блока */
    for (p=freep; !(bp > p && bp < p->s.ptr); p = p->s.ptr)
        if (p >= p->s.ptr && (bp > p || bp < p->s.ptr))
            break; /* освобождаем блок в начале или в конце */
        if (bp + bp->s.size == p->s.ptr) { /* слить с верхним */
            bp->s.size += p->s.ptr->s.size; /* соседом */
            bp->s.ptr = p->s.ptr->s.ptr;
        } else
            bp->s.ptr = p->s.ptr;
        if (p + p->s.size == bp) { /* слить с нижним соседом */
            p->s.size += bp->s.size;
            p->s.ptr = bp->s.ptr;
        } else
            p->s.ptr = bp;
    freep = p;
}


