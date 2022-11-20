#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int main()
{
    // if the buf is NULL and size is 0, getcwd automatically allocates the buffer with malloc
    char *str = getcwd(NULL, 0);

    // error checking
    if (str == NULL)
    {
        fprintf(stderr, "Cannot get current directory. Error: %s\n", strerror(errno));
        return EXIT_FAILURE;
    }

    printf("%s\n", str);
    free(str);

    return EXIT_SUCCESS;
}
