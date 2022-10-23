#include <stdio.h>
#include <stdlib.h>

#define FILENAME "00-input.txt"

int main() {
    /* open file in read mode */
    FILE *f = fopen(FILENAME, "r");
    if (f == NULL) {
        perror("[ERROR] Cannot open file '" FILENAME "'");
        exit(1);
    }

    /* read file char by char */
    char c;
    while ((c = fgetc(f)) != EOF) {
        printf("%c", c);
    }
    printf("\n");

    /* handle possible errors */
    if (ferror(f)) {
        perror("[ERROR] Failed to read file '" FILENAME "'");
        exit(2);
    }

    /* close file stream */
    fclose(f);

    return 0;
}
