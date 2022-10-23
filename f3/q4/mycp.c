#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OK 0

/**
 * @brief Copies a file
 *
 * On error, a message describing the fault is logged to `stderr` and the
 * program terminates immediately.
 *
 * @param src_filename
 * @param dest_filename
 * @retval OK
 */
int cp(const char *src_filename, const char *dest_filename) {
#define BUF_SIZE 256

    /* open both files */
    FILE *fsrc = fopen(src_filename, "r");
    if (fsrc == NULL) {
        fprintf(
            stderr,
            "[ERROR] Cannot open file '%s': %s\n",
            src_filename,
            strerror(errno));
        exit(2);
    }

    FILE *fdest = fopen(dest_filename, "w+");
    if (fdest == NULL) {
        fprintf(
            stderr,
            "[ERROR] Cannot open/create file '%s': %s\n",
            dest_filename,
            strerror(errno));
        exit(3);
    }

    /* read in chunks */
    char buf[BUF_SIZE];
    size_t bytes;
    while ((bytes = fread(buf, sizeof(char), BUF_SIZE, fsrc)) > 0) {
        if (fwrite(buf, sizeof(char), bytes, fdest) < bytes) {
            fprintf(
                stderr,
                "[ERROR] Failed to write to file '%s': %s\n",
                dest_filename,
                strerror(errno));
            fclose(fsrc);
            fclose(fdest);
            exit(4);
        }
    }

    /*
     * check for errors
     * did the loop terminate because of EOF or an error?
     */
    if (ferror(fsrc)) {
        fprintf(
            stderr,
            "[ERROR] Failed to read file '%s': %s\n",
            src_filename,
            strerror(errno));
        fclose(fsrc);
        fclose(fdest);
        exit(5);
    }

    fclose(fsrc);
    fclose(fdest);

    return OK;
}

/**
 * @brief Prints the correct usage for the program
 *
 * @param exe The name for the executable file
 */
void print_usage(const char *exe) {
    fprintf(stderr, "Usage: %s <src file> <dst file>\n", exe);
}

int main(int argc, char const *argv[]) {

    if (argc != 3) {
        print_usage(argv[0]);
        exit(1);
    }

    cp(argv[1], argv[2]);

    return 0;
}
