#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ERROR -1
#define OK 0

typedef enum { UPPER_CASE, LOWER_CASE, ORIGINAL } output_mode_t;

/**
 * @brief Transforms a string to lower case, upper case,
 * or leaves unchaged
 *
 * @param str The target string
 * @param mode The operation mode
 */
void transform_str(char *str, output_mode_t mode) {
    // leave string unchanged
    if (mode == ORIGINAL)
        return;

    for (size_t i = 0; i < strlen(str); i++) {
        if (mode == UPPER_CASE)
            str[i] = toupper(str[i]);
        else
            str[i] = tolower(str[i]);
    }
}

/**
 * @brief Reads, transforms and prints the contents of a file to the stdout
 *
 * @param filename The file's name
 * @param mode The transformation operation
 *
 * @retval ERROR - Failed to open the file, or error while reading it
 * @retval OK - Success
 */
int cat(const char *filename, output_mode_t mode) {
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
        transform_str(buf, mode);
        printf("%s", buf);
    }

    /*
     * check for errors
     * did the loop terminate because of EOF or an error?
     */
    if (ferror(f))
        return ERROR;

    /* close the file */
    printf("\n");
    fclose(f);

    return OK;
}

/**
 * @brief Prints the correct usage for the program
 *
 * @param exe The name for the executable file
 */
void print_usage(const char *exe) {
    fprintf(stderr, "Usage: %s <filename> [-u|-l]\n", exe);
}

int main(int argc, char const *argv[]) {

    if (argc < 2 || argc > 3) {
        print_usage(argv[0]);
        exit(1);
    }

    // default operating mode, do not transform the text
    output_mode_t m = ORIGINAL;

    // handle third optional argument
    if (argc == 3) {
        if (strcmp("-u", argv[2]) == 0) {
            m = UPPER_CASE;
        } else if (strcmp("-l", argv[2]) == 0) {
            m = LOWER_CASE;
        } else {
            fprintf(stderr, "Uknown option '%s'\n", argv[2]);
            print_usage(argv[0]);
            exit(2);
        }
    }

    // cat the file
    if (cat(argv[1], m) != OK) {
        fprintf(
            stderr,
            "[ERROR] Failed to cat file '%s': %s\n",
            argv[1],
            strerror(errno));
        exit(3);
    }

    return 0;
}
