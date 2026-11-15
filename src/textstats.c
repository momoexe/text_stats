#include <stdio.h>

#include "stats.h"

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
        fprintf(stderr, "Usage: textstats [FILE]\n");
        return 1;
    }

    // PRINT RESULT
    printf("[TEXT STATS]\n");
    printf("chars: %5zu\n", st.total_chars);
    printf("words: %5zu\n", st.total_words);
    printf("lines: %5zu\n", st.total_lines);

    return 0;
}