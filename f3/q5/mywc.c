#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUF_SIZE 256
#define ERROR 1
#define OK 0

typedef struct {
    uint32_t chars;
    uint32_t words;
    uint32_t lines;
} fstats_t;

/**
 * @brief Calculate statistics for a given text file (characters, words, lines)
 *
 * @param filename
 * @param stats
 *
 * @retval ERROR - Failed to open or read the text file. An error message is
 * logged to `stderr`
 * @retval OK - Text file processed and statistics are returned through the
 * parameter `stats`
 */
int mywc(const char *filename, fstats_t *stats) {
    /* open the file in read mode */
    FILE *f = fopen(filename, "r");
    if (f == NULL) {
        fprintf(
            stderr,
            "[ERROR] Failed to open file '%s': %s\n",
            filename,
            strerror(errno));
        return ERROR;
    }

    /* initialize all stats to zero */
    stats->chars = 0;
    stats->words = 0;
    stats->lines = 0;

    /* read file in chunks */
    char buf[BUF_SIZE];
    size_t bytes;
    bool isword = false; // when true, we are processing a sequence of
                         // alphanumeric characters (a word)

    while ((bytes = fread(buf, sizeof(char), BUF_SIZE, f)) > 0) {

        stats->chars += bytes;

        for (size_t i = 0; i < bytes; i++) {
            if (!isword && isalnum(buf[i])) {
                // found new word
                isword = true;
                stats->words++;
            } else if (isword && !(isalnum(buf[i]) || buf[i] == '-')) {
                // note: support hyphens in words
                // end of current word
                isword = false;
            }

            // handle newlines
            if (buf[i] == '\n')
                stats->lines++;
        }
    }

    /*
     * check for errors
     * did the loop terminate because of EOF or an error?
     */
    if (ferror(f)) {
        fprintf(
            stderr,
            "[ERROR] Failed to read file '%s': %s\n",
            filename,
            strerror(errno));
        return ERROR;
    }

    fclose(f);

    return OK;
}

/**
 * @brief Prints the correct usage for the program
 *
 * @param exe The name for the executable file
 */
void print_usage(const char *exe) {
    fprintf(stderr, "Usage: %s <file>\n", exe);
}

int main(int argc, char const *argv[]) {
    if (argc != 2) {
        print_usage(argv[0]);
        exit(1);
    }

    fstats_t stats;
    if (mywc(argv[1], &stats) != OK) {
        exit(2);
    }

    printf(
        "Statistics for file '%s'\n"
        "\tNum. of characters: %u\n"
        "\tNum. of words: %u\n"
        "\tNum. of lines: %u\n",
        argv[1],
        stats.chars,
        stats.words,
        stats.lines);

    return 0;
}
