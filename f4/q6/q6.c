#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>

int _print_file_type(const struct stat *s, const char *buf, const int pos)
{
    // '-' - Regular file.
    // 'd' - Directory.
    // 'c' - Character special file.
    // 'b' - Block special file.
    // 'p' - FIFO.S
    // 'l' - Symbolic link.
    // 's' - Socket.
    if (S_ISREG(s->st_mode))
    {
        return sprintf(buf + pos, "%c", "-");
    }
    else if (S_ISDIR(s->st_mode))
    {
        return sprintf(buf + pos, "%c", "d");
    }
    else if (S_ISCHR(s->st_mode))
    {
        return sprintf(buf + pos, "%c", "c");
    }
    else if (S_ISBLK(s->st_mode))
    {
        return sprintf(buf + pos, "%c", "b");
    }
    else if (S_ISFIFO(s->st_mode))
    {
        return sprintf(buf + pos, "%c", "p");
    }
    else if (S_ISLNK(s->st_mode))
    {
        return sprintf(buf + pos, "%c", "l");
    }
    else if (S_ISSOCK(s->st_mode))
    {
        return sprintf(buf + pos, "%c", "s");
    }
}

int _print_file_permissions(const struct stat *s, const char *buf, const int pos)
{
    
}
void print_file_info(char *fname)
{
    char buf[1024];
    int cur_pos = 0;

    struct stat s;
    stat(fname, &s);

    // print the file type
    cur_pos = _print_file_type(&s, buf, cur_pos);

    // print the file permissions
}

int main(int argc, char const *argv[])
{

    return 0;
}
