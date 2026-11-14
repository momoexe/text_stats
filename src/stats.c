#include <stdio.h>
#include <ctype.h>

#include "stats.h"

void stats_init(Stats* st){
    st->total_chars = 0;
    st->total_lines = 0;
    st->total_words = 0;
}

void stats_analyze(Stats* st, FILE* fp){
    stats_init(st);
    
    int sw = 0; // start word: a new word is started
    int sl = 0; // start line: a new line is started
    for(int c; (c = fgetc(fp)) != EOF;){
        st->total_chars++;

        if(!isspace(c) && !sw)
            sw = 1;
        else if(isspace(c) && sw){
            st->total_words++;
            sw = 0;
        }

        if(c != '\n' && !sl)
            sl = 1;
        else if(c == '\n'){
            st->total_lines++;
            sl = 0;
        }
    }
    
    if(sw)
        st->total_words++;
    if(sl)
        st->total_lines++;
    rewind(fp);
}