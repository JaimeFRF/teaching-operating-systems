#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <utime.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    const char *fname = argv[1];

    int fd = open(fname, O_CREAT | O_EXCL | O_WRONLY, 0644);

    if (fd == -1 && errno == EEXIST) {
        printf("File '%s' already exists! Changing access/modification times.\n", fname);
        utimes(fname, NULL);
    } else if (fd == 0) {
        printf("Created file '%s' successfully!\n", fname);
    } else {
        fprintf(stderr, "Cannot open file '%s'. Error: %s\n", fname, strerror(errno));
        return EXIT_FAILURE;
    }

    close(fd);
    return EXIT_SUCCESS;
}
