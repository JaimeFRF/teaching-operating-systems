#include <errno.h>
#include <stdio.h>
#include <string.h>

#define ERROR -1
#define OK 0

/**
 * @brief Cats a file text to stdout
 *
 * Reads the file in chunks of a given size and prints the chunk immediately,
 * avoiding memory pressure. As the file is read in chunks, we need to request
 * chunks one or more times.
 *
 * @param filename The filename
 *
 * @retval ERROR - Failed to open the file, or error while reading it
 * @retval OK - Success
 */
int cat(const char *filename) {
    #define BUF_SIZE 256

    /* open the file in read mode */
    FILE *f = fopen(filename, "r");
    if (f == NULL)
        return ERROR;

    /* read in chunks */
    char buf[BUF_SIZE];
    size_t bytes;
    while ((bytes = fread(buf, sizeof(char), BUF_SIZE - 1, f)) > 0) {
        buf[bytes] = '\0';
        printf("%s", buf);
    }

    /*
     * check for errors
     * did the loop terminate because of EOF or an error?
     */
    if (ferror(f))
        return ERROR;

    /* close the file */
    fclose(f);

    return OK;
}

int main(int argc, char const *argv[]) {

    for (int i = 1; i < argc; i++) {
        const char *filename = argv[i];
        printf("***** BEGIN '%s' *****\n", filename);
        int ret = cat(filename);
        if (ret == ERROR) {
            fprintf(
                stderr,
                "[ERROR] Failed to cat file '%s': %s",
                filename,
                strerror(errno));
        }
        printf("\n***** END '%s' *****\n", filename);
    }

    return 0;
}
