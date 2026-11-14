#include <stdio.h>

#include "stats.h"

int main(int argc, char **argv)
{

    char *filename = NULL;

    // OPTION HANDLING
    if (argc == 1)
    {
        printf("Usage: textstats [FILE]\n");
        return 0;
    }
    else if (argc == 2)
    {
        filename = argv[1];
    }
    else
    {
        printf("Usage: textstats [FILE]\n");
        return 0;
    }

    // FILE HANDLING
    FILE *fp = fopen(filename, "r");

    if (fp == NULL)
    {
        printf("textstats: %s: No such file\n", filename);
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