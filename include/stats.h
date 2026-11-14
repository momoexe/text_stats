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

size_t count_chars(FILE* fp);

size_t count_words(FILE* fp);

size_t count_lines(FILE* fp);




#endif