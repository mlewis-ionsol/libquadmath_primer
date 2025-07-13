#include <quadmath.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

static const __float128 RAD_TO_DEG = 180.0Q / M_PIq;
static const __float128 DEG_TO_RAD = M_PIq / 180.0Q;

__float128 rad2deg(__float128 rad) {
    return RAD_TO_DEG * rad;
}

__float128 deg2rad(__float128 deg) {
    return DEG_TO_RAD * deg;
}

void printResult(__float128 result) {
    char buf[128];
    quadmath_snprintf(buf, sizeof(buf), "%+-#46.*Qe", 20, result);
    printf("%s\n", buf);
}

int main(int argc, char **argv) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s -d|-r <value>\n", argv[0]);
        return 1;
    }

    __float128 val = strtoflt128(argv[2], NULL);
    if (isnanq(val)) {
        fprintf(stderr, "Error: Invalid input.\n");
        return 1;
    }

    if (strcmp(argv[1], "-d") == 0) {
        printResult(rad2deg(val));
        return 0;
    } else if (strcmp(argv[1], "-r") == 0) {
        printResult(deg2rad(val));
        return 0;
    }

    fprintf(stderr, "Error: Invalid option. Use -d or -r.\n");
    return 1;
}
