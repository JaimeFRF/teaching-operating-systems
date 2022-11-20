#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include <sys/time.h>
#include <fcntl.h>
#include <errno.h>
#include <utime.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    // auxiliar variable for + code readability
    const char *fname = argv[1];

    if (access(fname, F_OK) == -1)
    {
        // access failed, ensure the error is due pathname not existing
        if (errno != ENOENT)
        {
            fprintf(stderr, "Cannot stat file '%s'. Error: %s\n", fname, strerror(errno));
            return EXIT_FAILURE;
        }

        // access failed because file does not exist, so create it
        int fd;
        if ((fd = open(fname, O_CREAT, 0644)) == -1)
        {
            fprintf(stderr, "Cannot create file '%s'. Error: %s\n", fname, strerror(errno));
            return EXIT_FAILURE;
        }
        close(fd);
        printf("Created file %s!\n", fname);
    }
    else
    {
        // file exists, but is not necessarially a regular file (may be a directory)!
        
        // change the access/modification times
        if (utimes(fname, NULL) == -1)
        {
            fprintf(stderr, "Cannot change access/modification times for file '%s'. Error: %s\n", fname, strerror(errno));
            return EXIT_FAILURE;
        }

        printf("Changed modification time for file '%s'!\n", fname);
    }

    return EXIT_SUCCESS;
}
