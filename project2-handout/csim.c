#include "cachelab.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <strings.h>
#include <unistd.h>
#include <getopt.h>

int displayTrace = 0;
int indexBits;
int setNum;
int associativity;
int offsetBits;
int blockNum;
char *tracefile;
FILE *file;

int hits = 0, misses = 0, evictions = 0;

typedef struct {
  int time;
  uint64_t tag;
} cache_line;

int globalTime = 0;
cache_line **cache;


void usage(char *argv[]);
void init_cache();
void find_data(uint64_t tag, int index, char *result);
void destroy();

/* Print usage information */
void usage(char *argv[]) {
  printf("Usage: %s [-hv] -s <num> -E <num> -b <num> -t <file>\n"
         "Options:\n"
         "  -h         Print this help message.\n"
         "  -v         Optional verbose flag.\n"
         "  -s <num>   Number of set index bits.\n"
         "  -E <num>   Number of lines per set.\n"
         "  -b <num>   Number of block offset bits.\n"
         "  -t <file>  Trace file.\n"
         "\n"
         "Examples:\n"
         "  linux>  %s -s 4 -E 1 -b 4 -t traces/yi.trace\n"
         "  linux>  %s -v -s 8 -E 2 -b 4 -t traces/yi.trace\n", argv[0], argv[0], argv[0]);
}

/* Initiate the cache */
void init_cache() {
  cache = (cache_line **) malloc(sizeof(cache_line *) * setNum);
  for (int i = 0; i < setNum; ++i) {
    cache[i] = (cache_line *) malloc(sizeof(cache_line) * associativity);
    memset(cache[i], 0, sizeof(cache_line) * associativity);
  }
}


/* Destroy the cache */
void destroy() {
  for (int i = 0; i < setNum; ++i) {
    free(cache[i]);
  }
  free(cache);
}

/* Find data in the cache and store hit/miss information into char *result */
void find_data(uint64_t tag, int index, char *result) {
  cache_line *group = cache[index];
  int emptyLine = -1;
  for (int i = 0; i < associativity; ++i) {
    if (!group[i].time) {
      emptyLine = i;
    }
    else if (group[i].tag == tag) {
      group[i].time = globalTime;
      hits++;
      strcat(result, " hit");
      return;
    }
  }

  strcat(result, " miss");
  misses++;
  // If there is an empty line in the group
  if (emptyLine >= 0) {
    group[emptyLine].tag = tag;
    group[emptyLine].time = globalTime;
  }
  // If there is not an empty line in the group, we need to replace one of the lines
  else {
    strcat(result, " eviction");
    evictions++;
    int toReplace = 0;
    for (int i = 1; i < associativity; ++i) {
      if (group[i].time < group[toReplace].time)
        toReplace = i;
    }
    group[toReplace].tag = tag;
    group[toReplace].time = globalTime;
  }
}

int main(int argc, char *argv[]) {
  int opt;
  opterr = 0;
  int s_input = 0, E_input = 0, b_input = 0, t_input = 0;
  while ((opt = getopt(argc, argv, "hvs:E:b:t:")) != -1) {
    if (opt == 'h') {
      usage(argv);
      return 0;
    }
    else if (opt == 'v')
      displayTrace = 1;
    else if (opt == 's') {
      indexBits = atoi(optarg);
      setNum = 1 << indexBits;
      s_input = 1;
    }
    else if (opt == 'E') {
      associativity = atoi(optarg);
      E_input = 1;
    }
    else if (opt == 'b') {
      offsetBits = atoi(optarg);
      blockNum = 1 << offsetBits;
      b_input = 1;
    }
    else if (opt == 't') {
      tracefile = (char *) malloc((strlen(optarg) + 1) * sizeof(char));
      strcpy(tracefile, optarg);
      t_input = 1;
    }
    else if (opt == '?') {
      printf("%s: Missing required command line argument\n", argv[0]);
      usage(argv);
      return 0;
    }
  }

  // If one of the parameters is not defined, reprot error
  if (!(s_input && E_input && b_input && t_input)) {
    printf("%s: Missing required command line argument\n", argv[0]);
    usage(argv);
    return 0;
  }

  // Initailize the cache
  init_cache();

  file = fopen(tracefile, "r");
  if (!file) {
    printf("Fail to open %s!\n", tracefile);
  }

  char op[2];
  uint64_t address;
  int size;

  while (fscanf(file, "%s %lx, %d\n", op, &address, &size) != -1) {
    // Skip I instruction
    if (op[0] == 'I')
      continue;
    int index = (address >> offsetBits) & ~(~0u << indexBits);
    uint64_t tag = address >> (indexBits + offsetBits);

    ++globalTime;
    char result[20] = "";
    find_data(tag, index, result);
    // M instruction need to visit the cache twice
    if (op[0] == 'M') find_data(tag, index, result);
    if (displayTrace)
      printf("%s %lx,%d%s\n", op, address, size, result);
  }

  // Destroy the cache
  destroy();

  // Print summary
  printSummary(hits, misses, evictions);
  return 0;
}
