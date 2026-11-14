#ifndef STATS_H
#define STATS_H

#include <stdio.h>

typedef struct{
    size_t total_chars;
    size_t total_lines;
    size_t total_words;
} Stats;


void stats_init(Stats* st);

void stats_analyze(Stats* st, FILE* fp);




#endif