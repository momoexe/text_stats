#include <stdio.h>
#include <ctype.h>

#include "stats.h"

void stats_init(Stats* st){
    st->total_chars = 0;
    st->total_lines = 0;
    st->total_words = 0;
}

void stats_analyze(Stats* st, FILE* fp){
    st->total_chars = count_chars(fp); 
    st->total_words = count_words(fp); 
    st->total_lines = count_lines(fp); 
}

size_t count_chars(FILE* fp){
    size_t count = 0;
    
    for(int c; (c = fgetc(fp)) != EOF;){
        count++;
    }
    
    rewind(fp);
    return count;
}

size_t count_words(FILE* fp){
    size_t count = 0;
    int sw = 0; // start word: a new word is started
    for(int c; (c = fgetc(fp)) != EOF;){
        if(!isspace(c) && !sw)
            sw = 1;
        else if(isspace(c) && sw){
            count++;
            sw = 0;
        }
    }

    if(sw)
        count++;

    rewind(fp);
    return count;
}


size_t count_lines(FILE* fp){
    size_t count = 0;
    for(int c; (c = fgetc(fp)) != EOF;){
        if(c == '\n'){
            count++;
        }
    }
    if(count != 0)
        count++;

    rewind(fp);
    return count;
}