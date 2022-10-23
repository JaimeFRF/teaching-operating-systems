#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 128
#define FILENAME "00-input.txt"

int main() {
    /* open file in read mode */
    FILE *f = fopen(FILENAME, "r");
    if (f == NULL) {
        perror("[ERROR] Cannot open file '" FILENAME "'");
        exit(1);
    }

    /* read file by blocks */
    char buf[MAX_SIZE];
    size_t num_bytes;
    while ((num_bytes = fread(buf, sizeof(char), MAX_SIZE - 1, f)) > 0) {
        // insert the null-terminating null
        buf[num_bytes] = '\0';
        // print the string
        printf("%s", buf);
    }
    printf("\n");

    /* handle possible errors on fread */
    if (ferror(f)) {
        perror("[ERROR] Failed to read file '" FILENAME "'");
        exit(2);
    }

    /* close file stream */
    fclose(f);

    return 0;
}
