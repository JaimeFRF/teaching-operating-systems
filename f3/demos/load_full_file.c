#include <stdio.h>
#include <stdlib.h>

#define ERROR_CODE -1
#define FILENAME "00-input.txt"

/**
 * @brief Get the file's size in bytes
 *
 * @param f file
 * @retval -1 Error
 * @retval >0 The file size in bytes
 */
long get_file_size(FILE *f) {
    if (f == NULL)
        return -1;

    /* move pointer to the end of file stream */
    if (fseek(f, 0, SEEK_END) == ERROR_CODE) {
        perror("[ERROR] Cannot fseek() to the file's end");
        return -1;
    }

    /* get current stream position (in bytes) */
    long size;
    if ((size = ftell(f)) == ERROR_CODE) {
        perror("[ERROR] Cannot ftell()");
        return -1;
    }

    /* restore file position to the beginning of the file stream */
    rewind(f);
    // NOTE: `fseek(f, 0, SEEK_SET)` equivalent to `rewind(f)`

    return size;
}

int main() {
    /* open file in read mode */
    FILE *f = fopen("input.txt", "r");
    if (f == NULL) { // error
        perror("[ERROR] Cannot open file '" FILENAME "'");
        exit(1);
    }

    /* determine file size */
    long file_size = get_file_size(f);
    if (!file_size) {
        exit(2);
    }

    /* allocate memory buffer for the entire file content */
    char *buf = malloc(file_size + 1); // extra byte for '\0'
    if (buf == NULL) {
        perror("[ERROR] Cannot allocate memory to store the content of file "
               "'" FILENAME "'");
        exit(2);
    }

    /* read file with a single call to fread */
    fread(buf, sizeof(char), file_size, f);
    buf[file_size] = '\0';
    printf("%s\n", buf);

    /* close file stream and free memory*/
    fclose(f);
    free(buf);

    return 0;
}
