#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>

int bjorn1CountCodePoints(const uint8_t* s, size_t* count);
int bjorn2CountCodePoints(const uint8_t* s, size_t* count);
int cmpArithCountCodePoints(const uint8_t *s, size_t *count);
int cmpBranchCountCodePoints(const uint8_t *s, size_t *count);
int vimCountCodePoints(const uint8_t* s, size_t* count);

typedef int (cpcountfn)(const uint8_t *s, size_t *count);

#define NELEM(a) ( (sizeof(a)/sizeof(a)[0]) / !(sizeof(a)%sizeof(a)[0]) )
#define X(fn) \
    { fn, #fn }

void __attribute__ ((noinline)) bench_fn(const char *name, const uint8_t *buf, const char *funname, cpcountfn fn) {
    struct timeval t1, t2;
    double elapsedTime;
    int iterations = 8000;
    gettimeofday(&t1, NULL);
    size_t cnt = 0xDEAD;
    for (int i = 0; i < iterations; ++i) {
        fn(buf, &cnt);
    }
    gettimeofday(&t2, NULL); \
    elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;
    elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0;
    printf("%-15s|   %-25s|   %6.1f ms (count = %zu)\n", name, funname, elapsedTime, cnt);
}

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
    const char *fnames[] = {
        "text.txt",
        "normal.txt"
    };

    struct {
        cpcountfn *fn;
        const char *name;
    } xfns[] = {
        X(bjorn1CountCodePoints),
        X(bjorn2CountCodePoints),
        X(cmpArithCountCodePoints),
        X(cmpBranchCountCodePoints),
        X(vimCountCodePoints)
    };

    for (size_t f = 0; f < NELEM(fnames); ++f) {
        char *buf = readf(fnames[f]);
        for (size_t i = 0; i < NELEM(xfns); ++i) {
            bench_fn(fnames[f], (uint8_t *) buf, xfns[i].name, xfns[i].fn);
        }
        free(buf);
    }

    return 0;
}
