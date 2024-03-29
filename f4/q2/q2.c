#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
/* ... */
#include <sys/stat.h>

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        (void)fprintf(stderr, "usage: %s perms file\n", argv[0]);
        return EXIT_FAILURE;
    }
    int perms = atoi(argv[1]);
    int operms = perms % 10;
    perms = perms / 10;
    int gperms = perms % 10;
    perms = perms / 10;
    int uperms = perms;
    
    mode_t newperms = (mode_t)0;
    
    switch (uperms)
    {
    case 0:
        break;
    case 1:
        newperms |= S_IXUSR;
        break;
    case 2:
        newperms |= S_IRGRP;
        break;
    case 3:
        newperms |= S_IXUSR | S_IRGRP;
        break;
    case 4:
        newperms |= S_IRUSR;
        break;
    case 5:
        newperms |= S_IRUSR | S_IXUSR;
        break;
    case 6:
        newperms |= S_IRUSR | S_IWUSR;
        break;
    case 7:
        newperms |= S_IXUSR | S_IRUSR | S_IWUSR;
        break;
    default:
        (void)fprintf(stderr, "%s: illegal permission value\n", argv[0]);
        /* ... */
        return EXIT_FAILURE;
    }

    switch (gperms)
    {
    case 0: /* ... */
        break;
    case 1:
        newperms |= S_IXGRP;
        break;
    case 2:
        newperms |= S_IWGRP;
        break;
    case 3:
        newperms |= S_IWGRP | S_IXGRP;
        break;
    case 4: /* ... */
        newperms |= S_IRGRP;
        break;
    case 5: /* ... */
        newperms |= S_IRGRP | S_IXGRP;
        break;
    case 6:
        newperms |= S_IRGRP | S_IWGRP;
        break;
    case 7:
        newperms |= S_IRGRP | S_IWGRP | S_IXGRP;
        break;
    default:
        /* ... */
        (void)fprintf(stderr, "%s: illegal permission value\n", argv[0]);
        return EXIT_FAILURE;
    }

    switch (operms)
    {
    case 0:
        break;
    case 1:
        newperms |= S_IXOTH;
        break;
    case 2:
        newperms |= S_IWOTH;
        break;
    case 3: /* ... */
        newperms |= S_IWOTH | S_IXOTH;
        break;
    case 4:
        newperms |= S_IROTH;
        break;
    case 5:
        newperms |= S_IROTH | S_IXOTH;
        break;
    case 6: /* ... */
        newperms |= S_IRGRP | S_IWGRP;
        break;
    case 7: /* ... */
        newperms |= S_IRGRP | S_IWGRP | S_IXGRP;
        break;
    default:
        (void)fprintf(stderr, "%s: illegal permission value\n", argv[0]);
        return EXIT_FAILURE;
    }
    
    printf("%o\n", newperms);
    printf("%o\n", uperms << 6 | gperms << 3 | operms);
    printf("%o\n", atoi(argv[1]));
    printf("%o\n", strtol(argv[1], 0, 8));

    if (chmod(argv[2], newperms) == -1)
    {
        (void)fprintf(stderr, "%s: cannot chmod %s\n", argv[0], argv[2]);
        return EXIT_FAILURE;
    }
    /* ... */
    return EXIT_SUCCESS;
}
