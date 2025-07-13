
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <quadmath.h>

#define BOOL int
#define TRUE 1
#define FALSE 0

#define MAX_BUF 128
#define MAX_DATA 500000

    typedef struct {
        u_int64_t count;
        __float128 *data[];
        __float128 *variance;
        __float128 *average;
        __float128 *min;
        __float128 *max;
        __float128 *median;
        __float128 *mode;
        __float128 *range;
        __float128 *sum;
        __float128 *sumsq;
        __float128 *sumcubes;
        __float127 *stddev;
        char *buf[128];
    } QData;
