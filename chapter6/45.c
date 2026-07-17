/*
 * Caches (sum of all):
 * L1d:                       192 KiB (6 instances)
 * L1i:                       192 KiB (6 instances)
 * L2:                        3 MiB (6 instances)
 * L3:                        16 MiB (1 instance)
 *
 * so 192 Kib divided among 6 cores is 32 Kib of L1 cache per core
 * but let us suppose that half of the cache is being used by the 
 * function stack and variables so there's only 16 Kib of cache available
 * 
 * getconf LEVEL1_DCACHE_LINESIZE -> 64
 * so our cache line size is 64 Bytes 
 * that means we can have 16 ints in one cache line. Therefore out block-size
 * for blocking will be 16
 */

#include <stdio.h>
#include <stdlib.h>

#define BLOCK 16
#define DIM 1024
#define REPS 200

// function to test that is our transpose matrix correct
int correct(int *dst, int *src, int dim) {
    for (int i = 0; i < dim; i++)
        for (int j = 0; j < dim; j++)
            if (dst[j*dim+i] != src[i*dim+j]) return 0;
    return 1;
}

// the transpose function from the problem statement
void transpose(int *dst, int *src, int dim)
{
    int i, j;
    for (i = 0; i < dim; i++)
        for (j = 0; j < dim; j++)
            dst[j*dim + i] = src[i*dim + j];
}

// my optimised_transpose function for better cache usage
void optimised_transpose(int *dst, int *src, int dim) {
    for (int bi = 0; bi < dim; bi += BLOCK) { // for row of BxB blocks
        for (int bj = 0; bj < dim; bj += BLOCK) { // for columns of BxB block
            for (int ii = bi; ii < (bi+BLOCK < dim ? bi+BLOCK : dim); ii++) {
                for (int jj = bj; jj < (bj+BLOCK < dim ? bj+BLOCK : dim); jj++) {
                    dst[jj*dim + ii] = src[ii*dim + jj];
                }
            }
        }
    } 
}


int main() {
    int dim = DIM, reps = REPS;
    int *src = malloc(dim * dim * sizeof(int));
    int *dst = malloc(dim * dim * sizeof(int));
    for (int k = 0; k < dim * dim; k++) src[k] = k;

    // warm-up call: pages get faulted in now, not during the measured loop
    optimised_transpose(dst, src, dim);

    for (int r = 0; r < reps; r++) {
        optimised_transpose(dst, src, dim);
    }

    free(src); free(dst);
    return 0;
}

/*
  sudo perf stat -e cycles,instructions,cache-references,cache-misses,L1-dcache-loads,L1-dcache-load-misses ./optimised

 Performance counter stats for './optimised':

       2,26,07,669      cycles                                                                  (55.25%)
       1,51,44,158      instructions                     #    0.67  insn per cycle
         41,42,544      cache-references
          6,09,402      cache-misses                     #   14.71% of all cache refs
         51,90,947      L1-dcache-loads
         48,46,636      L1-dcache-load-misses            #   93.37% of all L1-dcache accesses   (44.75%)

       0.006076268 seconds time elapsed

       0.006144000 seconds user
       0.000000000 seconds sys
*/

/*
  sudo perf stat -e cycles,instructions,cache-references,cache-misses,L1-dcache-loads,L1-dcache-load-misses ./naive

 Performance counter stats for './naive':

       3,28,81,224      cycles                                                                  (48.87%)
       1,36,50,115      instructions                     #    0.42  insn per cycle              (85.52%)
         62,31,257      cache-references
         18,30,025      cache-misses                     #   29.37% of all cache refs
         51,16,827      L1-dcache-loads
         57,55,242      L1-dcache-load-misses            #  112.48% of all L1-dcache accesses   (65.61%)

       0.009067708 seconds time elapsed

       0.009173000 seconds user
       0.000000000 seconds sys
*/
