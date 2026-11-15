#include <stdio.h>
#include <string.h>

#include "stats.h"

static void print_usage(FILE* stream);

int main(int argc, char **argv)
{
    const char *filename = NULL;
    Stats st;
    int ch = 0;
    int wd = 0;
    int ln = 0;

    for(int i = 1; i < argc; i++){
        if(strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0){
            print_usage(stdout);
            return 0;
        }
        else if(strcmp(argv[i], "-c") == 0)
            ch = 1;
        else if(strcmp(argv[i], "-w") == 0)
            wd = 1;
        else if(strcmp(argv[i], "-l") == 0)
            ln = 1;
        else{
            if(!filename)
                filename = argv[i];
            else{
                print_usage(stderr);
                return 1;
            }
        }
    }

    if(filename != NULL){
        FILE *fp = fopen(filename, "r");
        if (fp == NULL)
        {
            fprintf(stderr, "textstats: %s: No such file\n", filename);
            return 1;
        }
        stats_analyze(&st, fp);
        fclose(fp);
    }
    else{
        stats_analyze(&st, stdin);
    }

    if(!ch && !wd && !ln){
        ch = 1;
        wd = 1;
        ln = 1;
    }

    printf("[TEXT STATS]\n");
    if(ch)
        printf("chars: %5zu\n", st.total_chars);
    if(wd)
        printf("words: %5zu\n", st.total_words);
    if(ln)
        printf("lines: %5zu\n", st.total_lines);

    return 0;
}

static void print_usage(FILE* stream){
    fprintf(stream,
            "Usage:\n"
            "  textstats [OPTION]... [FILE]\n"
            "  textstats -h | --help\n"
            "\n"
            "Analyze FILE, or standard input if FILE is omitted.\n"
            "\n"
            "Options:\n"
            "  -c           show character count\n"
            "  -w           show word count\n"
            "  -l           show line count\n"
            "  -h, --help   show this help\n");
}