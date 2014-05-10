#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int bjorn1CountCodePoints(const uint8_t* s, size_t* count);
int bjorn2CountCodePoints(const uint8_t* s, size_t* count);
int cmpArithCountCodePoints(const uint8_t *s, size_t *count);
int cmpBranchCountCodePoints(const uint8_t *s, size_t *count);
int vimCountCodePoints(const uint8_t* s, size_t* count);

typedef int (cpcountfn)(const uint8_t *s, size_t *count);

#define NELEM(a) ( (sizeof(a)/sizeof(a)[0]) / !(sizeof(a)%sizeof(a)[0]) )
#define X(fn) \
    { fn, #fn }

#define MAX_NAME_SIZE 256

#define MODE_GITHUB 0x1

struct result {
    char file[MAX_NAME_SIZE];
    char method[MAX_NAME_SIZE];
    double runtime;
    double bytes_per_codepoint;
    double mb_per_sec;
};

void bench_fn(const char *name,
              int it,
              long fsize,
              const uint8_t *buf,
              const char *funname,
              cpcountfn fn,
              struct result *res) {
    struct timeval t1, t2;
    double elapsedTime;

    gettimeofday(&t1, NULL);
    size_t cnt = 0xDEAD;
    for (int i = 0; i < it; ++i) {
        fn(buf, &cnt);
    }
    gettimeofday(&t2, NULL);

    elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;
    elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0;

    double mb = (((double)fsize) / 1024.0 / 1024.0) * it;
    double sec = elapsedTime / 1000.0;
    double bytes_codepoint_ratio = ((double)fsize) / (double)cnt;

    strncpy(res->file, name, sizeof(res->file));
    strncpy(res->method, funname, sizeof(res->method));
    res->runtime = elapsedTime;
    res->bytes_per_codepoint = bytes_codepoint_ratio;
    res->mb_per_sec = mb / sec;
}

char *readf(const char *fname, long *fsize) {
    FILE *f = fopen(fname, "rb");
    if (f == NULL) {
        return NULL;
    }

    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    rewind(f);

    char *buf = malloc(size + 1);
    fread(buf, size, 1, f);
    fclose(f);

    buf[size] = 0;

    *fsize = size;

    return buf;
}

int cmp_results(const void * a, const void * b) {
  const struct result *r1 = a;
  const struct result *r2 = b;

  return r2->mb_per_sec - r1->mb_per_sec;
}

char *wrapstring(char *buf, char *wrapper, size_t max) {
    char tmp[MAX_NAME_SIZE] = {0};

    size_t len = strlen(buf);
    size_t wraplen = strlen(wrapper);
    size_t buflen = len + 2 * wraplen;
    if (len >= MAX_NAME_SIZE || buflen >= max) {
        return buf;
    }

    strncpy(tmp, buf, sizeof(tmp));
    memcpy(buf, wrapper, wraplen);
    memcpy(buf + wraplen, tmp, len);
    memcpy(buf + wraplen + len, wrapper, wraplen + 1);

    return buf;
}

char *dtos(double num, char *buf, size_t len) {
   snprintf(buf, len, "%.1f", num);
   return buf;
}

void print_results(const struct result *results, size_t num, uint32_t mode) {
    printf("file           | function                 | runtime   | bytes/codepoint | mb/sec\n");
    printf("---------------|--------------------------|-----------|-----------------|-------\n");
    for (size_t i = 0; i < num; ++i) {
        struct result res = results[i];
        if (mode & MODE_GITHUB && i == 0) {
            char runtime_str[MAX_NAME_SIZE];
            char bytes_per_codepoint_str[MAX_NAME_SIZE];
            char mb_per_sec_str[MAX_NAME_SIZE];
            dtos(res.runtime, runtime_str, sizeof(runtime_str));
            dtos(res.bytes_per_codepoint, bytes_per_codepoint_str, sizeof(bytes_per_codepoint_str));
            dtos(res.mb_per_sec, mb_per_sec_str, sizeof(mb_per_sec_str));

            printf("%-15s| %-25s| %s | %s | %s\n",
                wrapstring(res.file, "**", sizeof(res.file)),
                wrapstring(res.method, "**", sizeof(res.method)),
                wrapstring(runtime_str, "**", sizeof(runtime_str)),
                wrapstring(bytes_per_codepoint_str, "**", sizeof(bytes_per_codepoint_str)),
                wrapstring(mb_per_sec_str, "**", sizeof(mb_per_sec_str)));
        }
        else {
            printf("%-15s| %-25s| %6.1f ms | %15.1f | %3.1f\n",
                res.file, res.method, res.runtime, res.bytes_per_codepoint, res.mb_per_sec);
        }
    }
}

int main(int argc, char **argv) {
    (void)argv;

    uint32_t mode = 0;
    if (argc > 1) {
        mode |= MODE_GITHUB;
    }

    struct {
        const char *name;
        int iterations;
    } files[] = {
        { "text/utf8.txt", 4000 },
        { "text/ascii.txt", 4000 },
        { "text/enwik8.txt", 1 }
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

    for (size_t f = 0; f < NELEM(files); ++f) {
        long fsize = 0;
        char *buf = readf(files[f].name, &fsize);
        if (!buf) {
            continue;
        }

        struct result results[NELEM(xfns)];

        for (size_t i = 0; i < NELEM(xfns); ++i) {
            bench_fn(files[f].name, files[f].iterations, fsize,
                (uint8_t *) buf,
                xfns[i].name, xfns[i].fn,
                &results[i]);
        }

        qsort(results, NELEM(results), sizeof(results[0]), cmp_results);
        print_results(results, NELEM(results), mode);

        free(buf);
        printf("\n");
    }

    return 0;
}
