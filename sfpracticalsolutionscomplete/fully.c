#include <stdio.h>
#include <stdlib.h>

#define CACHE_SIZE 16
#define BLOCK_SIZE 4  // Adjust this based on your actual block size

typedef struct {
    int valid;
    int tag;
} CacheLine;

CacheLine cache[CACHE_SIZE];

void initCache() {
    for (int i = 0; i < CACHE_SIZE; i++) {
        cache[i].valid = 0;
        cache[i].tag = -1;
    }
}

int readFromCache(int address) {
    int index = (address / BLOCK_SIZE) % CACHE_SIZE;
    int tag = address / (CACHE_SIZE * BLOCK_SIZE);

    for (int i = 0; i < CACHE_SIZE; i++) {
        if (cache[i].valid && cache[i].tag == tag) {
            return 1; // Cache hit
        }
    }

    for (int i = 0; i < CACHE_SIZE; i++) {
        if (!cache[i].valid) {
            cache[i].valid = 1;
            cache[i].tag = tag;
            return 0; // Cache miss
        }
    }

    return 0;
}

int main() {
    initCache();

    FILE *traceFile;
    traceFile = fopen("trace.txt", "r");

    if (traceFile == NULL) {
        perror("Error opening trace file");
        return 1;
    }

    char line[50];
    int hits = 0;
    int accesses = 0;

    while (fgets(line, sizeof(line), traceFile)) {
        unsigned int address;
        sscanf(line, "%x", &address);

        if (readFromCache(address)) {
            hits++;
        }

        accesses++;
    }

    fclose(traceFile);

    printf("Final number of hits: %d\n", hits);
    printf("Final number of accesses: %d\n", accesses);
    printf("Cache hit rate: %.2f%%\n", (float)hits / accesses * 100);

    return 0;
}
