#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[])
{
    /* check if exactly one argument is present */
    if (argc != 2)
    {
        fprintf(stderr, "Usage: cat <filename>\n");
        return EXIT_FAILURE;
    }
    
    /* check if file can be opened and is readable */
    int fd = open(argv[1], O_RDONLY);
    
    if (fd == -1)
    {
        fprintf(stderr, "Cannot open file %s\nError: %s", argv[1], strerror(errno));
        return EXIT_FAILURE;
    }

    /* print the contents in blocks */
    char buffer[BUFFER_SIZE];
    ssize_t count;
    while ((count = read(fd, buffer, BUFFER_SIZE)) > 0)
    {
        // while the number of read bytes is > 0, then success
        // if it is 0, the end of file was reached
        // if it is -1, then error (handled below)
        write(STDOUT_FILENO, buffer, count);
    }

    /* check for error */
    if (count == -1) {
        perror("Something went wrong while reading the file");
        close(fd);
        return EXIT_FAILURE;
    }

    printf("\n");

    /* close file */
    close(fd);
    return EXIT_SUCCESS;
}
