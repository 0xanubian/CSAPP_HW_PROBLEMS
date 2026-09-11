static void place(void *bp, size_t asize)
{
    size_t allocated_size = GET_SIZE(HDRP(bp));

    if (allocated_size - asize >= 2*DSIZE) {
        PUT(HDRP(bp), PACK(asize, 1));
        PUT(FTRP(bp), PACK(asize, 1));
        bp = NEXT_BLKP(bp);
        PUT(HDRP(bp), PACK(allocated_size - asize, 0));
        PUT(HDRP(bp), PACK(allocated_size - asize, 0));
    }

    else {
        PUT(HDRP(bp), PACK(allocated_size, 1));
        PUT(FTRP(bp), PACK(allocated_size, 1));
    }
}
