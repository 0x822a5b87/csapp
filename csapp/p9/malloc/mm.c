//
// Created by 杜航宇 on 2019/12/5.
//

#include "memlib.c"

#define WSIZE 4                         // Word and header/footer size (bytes)
#define DSIZE 8                         // Double word size (bytes)
#define CHUNKSIZE (1 << 12)             // Extend heap by this amount
#define MINCHUNK (2 * DSIZE)            // min chunk size

#define MAX(x, y) ((x) > (y) ? (x) : (y))

#define PACK(size, alloc) ((size) | (alloc))

// Read the size and allocated fields from address p
#define GET(p) (*(unsigned int *) (p))
#define PUT(p, val) (* (unsigned int *) (p) = (val))

#define GET_SIZE(p)  (GET(p) & ~0x7)
#define GET_ALLOC(p) (GET(p) & 0x1)

// Given block ptr bp, compute address of its header and footer
#define HDRP(bp) ((char *) (bp) - WSIZE)
#define FTRP(bp) ((char *) (bp) + GET_SIZE(HDRP(bp)) - DSIZE)

// Given block ptr bp, compute address of next and previous blocks
#define NEXT_BLKP(bp) ((char *) (bp) + GET_SIZE(((char *)(bp) - WSIZE)))
#define PREV_BLKP(bp) ((char *) (bp) - GET_SIZE(((char *)(bp) - DSIZE)))

static void *extend_heap(size_t words);

static void *coalesce(void *bp);

// asize 已经是计算了 head 和 foot 的
static void *find_fit(size_t asize);

static void place(void *bp, size_t asize);

int mmm_init();

void *mmm_malloc(size_t size);


// 初始化堆
// 第一个字是为了双字节对齐使用的填充字（因为 prologue block 双字，而 epilogue 单字）
// 随后一个大小为 8 的已分配块作为 prologue bock
// 以 0 结尾的 epilogue，仅有头没有尾
int mmm_init()
{
    if ((heap_listp = mmem_sbrk(4 * WSIZE)) == (void *) -1)
    {
        return -1;
    }
    PUT(heap_listp, 0);
    PUT(heap_listp + (1 * WSIZE), PACK(DSIZE, 1));
    PUT(heap_listp + (2 * WSIZE), PACK(DSIZE, 1));
    PUT(heap_listp + (3 * WSIZE), PACK(0, 1));
    heap_listp += (2 * WSIZE);

    if (extend_heap(CHUNKSIZE / WSIZE) == NULL)
    {
        return -1;
    }
    return 0;
}

void *mm_malloc(size_t size)
{
    size_t asize;
    size_t extendsize;
    char   *bp;

    if (size == 0)
        return NULL;

    if (size < DSIZE)
        asize = MINCHUNK;
    else
        // 内存二字节对齐
        asize = DSIZE * ((size + (DSIZE) + (DSIZE - 1)) / DSIZE);

    if ((bp = find_fit(asize)) != NULL)
    {
        place(bp, asize);
        return bp;
    }

    extendsize = MAX(asize, CHUNKSIZE);
    if ((bp    = extend_heap(extendsize / WSIZE)) == NULL)
        return NULL;
    place(bp, asize);
    return bp;
}

void *find_fit(size_t asize)
{
    void *bp;
    for (bp = heap_listp; GET_SIZE(HDRP(bp)) > 0; bp = NEXT_BLKP(bp))
    {
        if (!GET_ALLOC(HDRP(bp)) && GET_SIZE(HDRP(bp)) >= asize)
        {
            return bp;
        }
    }
    return NULL;
}

void place(void *bp, size_t asize)
{
    size_t total     = GET_SIZE(HDRP(bp));
    size_t remaining = total - asize;
    if (remaining >= MINCHUNK)
    {
        // 如果剩余部分大于最小块那么进行分割，并且我们还需要考虑最小快的内存对问题
        PUT(HDRP(bp), PACK(asize, 1));
        PUT(FTRP(bp), PACK(asize, 1));
        PUT(HDRP(NEXT_BLKP(bp)), PACK(remaining, 0));
        PUT(FTRP(NEXT_BLKP(bp)), PACK(remaining, 0));
    }
    else
    {
        PUT(HDRP(bp), PACK(total, 1));
        PUT(FTRP(bp), PACK(total, 1));
    }
}

static void *extend_heap(size_t words)
{
    char   *bp;
    size_t size;
    size           = (words % 2) ? (words + 1) * WSIZE : words * WSIZE;
    if ((long) (bp = mmem_sbrk(size)) == -1)
    {
        return NULL;
    }

    PUT(HDRP(bp), PACK(size, 0));
    PUT(FTRP(bp), PACK(size, 0));
    PUT(HDRP(NEXT_BLKP(bp)), PACK(0, 1));

    return coalesce(bp);
}

void mm_free(void *bp)
{
    size_t size = GET_SIZE(bp);
    PUT(HDRP(bp), PACK(size, 0));
    PUT(FTRP(bp), PACK(size, 0));
    coalesce(bp);
}

static void *coalesce(void *bp)
{
    size_t prev_alloc = GET_ALLOC(FTRP(PREV_BLKP(bp)));
    size_t next_alloc = GET_ALLOC(HDRP(NEXT_BLKP(bp)));
    size_t size       = GET_SIZE(HDRP(bp));

    if (prev_alloc && next_alloc)
    {
        return bp;
    }
    else if (prev_alloc && !next_alloc)
    {
        size += GET_SIZE(HDRP(NEXT_BLKP(bp)));
        PUT(HDRP(bp), PACK(size, 0));
        PUT(FTRP(bp), PACK(size, 0));
    }
    else if (!prev_alloc && next_alloc)
    {
        size += GET_SIZE(HDRP(PREV_BLKP(bp)));
        PUT(FTRP(bp), PACK(size, 0));
        PUT(HDRP(PREV_BLKP(bp)), PACK(size, 0));
        bp = PREV_BLKP(bp);
    }
    else
    {
        size += GET_SIZE(HDRP(PREV_BLKP(bp))) + GET_SIZE(FTRP(NEXT_BLKP(bp)));
        PUT(HDRP(PREV_BLKP(bp)), PACK(size, 0));
        PUT(FTRP(NEXT_BLKP(bp)), PACK(size, 0));
        bp = PREV_BLKP(bp);
    }

    return bp;
}

