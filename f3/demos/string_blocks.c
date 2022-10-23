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
    while (fgets(buf, MAX_SIZE, f) != NULL) {
        printf("%s", buf); // print the string
    }
    printf("\n");

    /* handle possible errors on fgets */
    if (ferror(f)) {
        perror("[ERROR] Failed to read file '" FILENAME "'");
        exit(2);
    }

    /* close file stream */
    fclose(f);

    return 0;
}
