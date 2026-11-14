#include <stdio.h>

#include "stats.h"

int main(int argc, char **argv)
{

    const char *filename = NULL;

    // OPTION HANDLING
    if (argc == 1)
    {
        fprintf(stderr, "Usage: textstats [FILE]\n");
        return 1;
    }
    else if (argc == 2)
    {
        filename = argv[1];
    }
    else
    {
        fprintf(stderr, "Usage: textstats [FILE]\n");
        return 1;
    }

    // FILE HANDLING
    FILE *fp = fopen(filename, "r");

    if (fp == NULL)
    {
        fprintf(stderr, "textstats: %s: No such file\n", filename);
        return 1;
    }

    // ANALYZE
    Stats st;
    stats_init(&st);
    stats_analyze(&st, fp);

    fclose(fp);

    // PRINT RESULT
    printf("[TEXT STATS]\n");
    printf("chars: %5zu\n", st.total_chars);
    printf("words: %5zu\n", st.total_words);
    printf("lines: %5zu\n", st.total_lines);

    return 0;
}