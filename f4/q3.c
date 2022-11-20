#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <pwd.h>
#include <string.h>
#include <errno.h>

int file_stat(const char *fname)
{
    struct stat info;
    if (lstat(fname, &info) == -1)
    {
        fprintf(stderr, "Cannot obtain statistics for file '%s'. Error: %s\n", fname, strerror(errno));
        return EXIT_FAILURE;
    }

    // print the filename
    printf("'%s' stats:\n", fname);

    // print the file size in bytes
    printf("\tsize: %ld bytes\n", info.st_size);

    // print the number of blocks on disk
    printf("\tdisk_blocks: %ld\n", info.st_blocks);

    // print the user identifier
    // Note: user and group identifiers are numbers. See /etc/passwd
    printf("\tuser owner (uid): %u\n", info.st_uid);

    // Note: you can get the username using `getpwnam`
    // Tip: Use `man -k "<regex>"` to search for functions/commands that
    // include certain keywords. For instance, I want a username from the
    // indetifier. I used `man -k "user.*id"` and found the function I needed.
    // C functions are typically available in sections 2 and 3,
    // you can ignore results like `logname (1)` because section 1 is for
    // shell/bash command. Not super easy to search... but might be useful in
    // exams
    printf("\tuser owner (name): %s\n", getpwuid(info.st_uid)->pw_name);

    // The times in the info struct are unix/epoch times, i.e., number of seconds
    // elapsed since 1 jan 1970. You can use 'ctime' to conver  t it to a local
    // time string that is automatically formatted accordingly with system
    // settings (dates and times representation vary from region to region)
    printf("\tmodification time (ctime): %s\n", ctime(&info.st_mtime));

    // If you want to customise the time format, you can opt by `gmtime` or
    // `localtime`, which are C standard. They take the epoch time and return
    // a structure with detailed fields, i.e., month, year, hour, ...
    struct tm *mod_time = localtime(&info.st_mtime);
    // Note: '%02d' prints the number with width 2 and fills empty spaces with 0's
    // If the day number is '1' it prints '01'
    // Note: some values in the struct tm are not the real value and require
    // some shifting. Read 'man'. E.g., The months are 0-indexed. The year is
    // decremented by 1900.
    printf("\tmodification time (localtime): %02d/%02d/%04d %02d:%02d\n",
           mod_time->tm_mday,
           mod_time->tm_mon + 1,
           mod_time->tm_year + 1900,
           mod_time->tm_hour,
           mod_time->tm_min);
    // Similar to localtime, but uses the UTC timezone
    mod_time = gmtime(&info.st_mtime);
    printf("\tmodification time (gmtime): %02d/%02d/%04d %02d:%02d (UTC)\n",
           mod_time->tm_mday,
           mod_time->tm_mon + 1,
           mod_time->tm_year + 1900,
           mod_time->tm_hour,
           mod_time->tm_min);
    return EXIT_SUCCESS;
}

int main(int argc, char *argv[])
{
    file_stat(argv[1]);
}
