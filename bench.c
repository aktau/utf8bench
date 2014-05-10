/* #include "all.h" */

#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>

int bjorn1CountCodePoints(const uint8_t* s, size_t* count);
int bjorn2CountCodePoints(const uint8_t* s, size_t* count);
int cmpArithCountCodePoints(const uint8_t *s, size_t *count);
int cmpBranchCountCodePoints(const uint8_t *s, size_t *count);
int vimCountCodePoints(const uint8_t* s, size_t* count);

/* if (fn(buf, &cnt)) { \ */
/*     printf("malformed string\n"); \ */
/* } \ */
/* else { \ */
/*     printf("correct string, %zu codepoints\n", cnt); \ */
/* } \ */

#define BENCH(name, buf, fn) \
    do { \
    struct timeval t1, t2; \
    double elapsedTime; \
    int iterations = 8000; \
    gettimeofday(&t1, NULL); \
    size_t cnt = 0xDEAD; \
    for (int i = 0; i < iterations; ++i) { \
        fn(buf, &cnt); \
    } \
    gettimeofday(&t2, NULL); \
    elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0; \
    elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0; \
    printf(name #fn ": %6.1f ms (count = %zu)\n", elapsedTime, cnt); \
    } while (0)

/* void __attribute__ ((noinline)) bench_bram(const short *g1, size_t c1, const short *g2, size_t c2, int op, short *clstr) { */
/*     BENCH(syn_combine_list_merge(g1, g2, op, clstr)); */
/* } */

char *readf(const char *fname) {
    FILE *f = fopen(fname, "rb");
    fseek(f, 0, SEEK_END);
    long fsize = ftell(f);
    rewind(f);

    char *buf = malloc(fsize + 1);
    fread(buf, fsize, 1, f);
    fclose(f);

    buf[fsize] = 0;

    return buf;
}

int main() {
    char *buf = readf("text.txt");

    BENCH("multibyte: ", (uint8_t *) buf, bjorn1CountCodePoints);
    BENCH("multibyte: ", (uint8_t *) buf, bjorn2CountCodePoints);
    BENCH("multibyte: ", (uint8_t *) buf, cmpArithCountCodePoints);
    BENCH("multibyte: ", (uint8_t *) buf, cmpBranchCountCodePoints);
    BENCH("multibyte: ", (uint8_t *) buf, vimCountCodePoints);

    free(buf);

    buf = readf("normal.txt");

    BENCH("ascii:     ", (uint8_t *) buf, bjorn1CountCodePoints);
    BENCH("ascii:     ", (uint8_t *) buf, bjorn2CountCodePoints);
    BENCH("ascii:     ", (uint8_t *) buf, cmpArithCountCodePoints);
    BENCH("ascii:     ", (uint8_t *) buf, cmpBranchCountCodePoints);
    BENCH("ascii:     ", (uint8_t *) buf, vimCountCodePoints);

    free(buf);

    /* size_t cnt = 0xDEAD; */
    /* if (countCodePoints((uint8_t *)buf, &cnt)) { */
    /*     printf("malformed string\n"); */
    /* } */
    /* else { */
    /*     printf("correct string, %zu codepoints\n", cnt); */
    /* } */

    /* cnt = 0xDEAD; */
    /* if (vimCountCodePoints((uint8_t *)buf, &cnt)) { */
    /*     printf("malformed string\n"); */
    /* } */
    /* else { */
    /*     printf("correct string, %zu codepoints\n", cnt); */
    /* } */

    return 0;
}
