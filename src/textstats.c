#include <stdio.h>
#include <string.h>

#include "stats.h"

static void print_usage(FILE* stream);

int main(int argc, char **argv)
{

    const char *filename = NULL;
    Stats st;

    // OPTION HANDLING
    if (argc == 1)
    {
        stats_analyze(&st, stdin);
    }
    else if (argc == 2)
    {
        if(strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0){
            print_usage(stdout);
            return 0;
        }

        filename = argv[1];
        FILE *fp = fopen(filename, "r");

        if (fp == NULL)
        {
            fprintf(stderr, "textstats: %s: No such file\n", filename);
            return 1;
        }

        stats_analyze(&st, fp);

        fclose(fp);
    }
    else
    {
        print_usage(stderr);
        return 1;
    }

    // PRINT RESULT
    printf("[TEXT STATS]\n");
    printf("chars: %5zu\n", st.total_chars);
    printf("words: %5zu\n", st.total_words);
    printf("lines: %5zu\n", st.total_lines);

    return 0;
}


static void print_usage(FILE* stream){
    fprintf(stream,
            "Usage:\n"
            "  textstats [FILE]\n"
            "  textstats -h | --help\n"
            "\n"
            "Analyze FILE, or standard input if FILE is omitted.\n");
}