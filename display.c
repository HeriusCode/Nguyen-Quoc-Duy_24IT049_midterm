#include <stdio.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <ctype.h>
#include <unistd.h>

#include "display.h"

static void
print_mode(mode_t mode)
{
    char type;

    if (S_ISREG(mode))
        type = '-';
    else if (S_ISDIR(mode))
        type = 'd';
    else if (S_ISLNK(mode))
        type = 'l';
    else if (S_ISCHR(mode))
        type = 'c';
    else if (S_ISBLK(mode))
        type = 'b';
    else if (S_ISFIFO(mode))
        type = 'p';
    else if (S_ISSOCK(mode))
        type = 's';
    else
        type = '?';

    printf("%c", type);

    printf("%c", (mode & S_IRUSR) ? 'r' : '-');
    printf("%c", (mode & S_IWUSR) ? 'w' : '-');
    printf("%c", (mode & S_ISUID) ?
        ((mode & S_IXUSR) ? 's' : 'S') :
        ((mode & S_IXUSR) ? 'x' : '-'));

    printf("%c", (mode & S_IRGRP) ? 'r' : '-');
    printf("%c", (mode & S_IWGRP) ? 'w' : '-');
printf("%c",
        (mode & S_ISGID) ?
        ((mode & S_IXGRP) ? 's' : 'S') :
        ((mode & S_IXGRP) ? 'x' : '-'));



 printf("%c", (mode & S_IROTH) ? 'r' : '-');
    printf("%c", (mode & S_IWOTH) ? 'w' : '-');
    printf("%c", (mode & S_ISVTX) ?
        ((mode & S_IXOTH) ? 't' : 'T') :
        ((mode & S_IXOTH) ? 'x' : '-'));
}

static void
print_size(long long size, const Options *options)
{
    if (options->size_mode != SIZE_HUMAN) {
        printf("%lld", size);
        return;
    }

    if (size < 1024) {
        printf("%lldB", size);
    } else if (size < 1024 * 1024) {
        printf("%.1fK", (double)size / 1024.0);
    } else if (size < 1024LL * 1024LL * 1024LL) {
        printf("%.1fM", (double)size /
            (1024.0 * 1024.0));
    } else {
        printf("%.1fG", (double)size /
            (1024.0 * 1024.0 * 1024.0));
    }
}

static void
print_classification(const FileInfo *info)
{
    mode_t mode;

    mode = info->st.st_mode;

    if (S_ISDIR(mode))
        printf("/");
    else if (S_ISLNK(mode))
        printf("@");
    else if (S_ISFIFO(mode))
        printf("|");
    else if (S_ISSOCK(mode))
        printf("=");
    else if (S_ISREG(mode) &&
        (mode & (S_IXUSR | S_IXGRP | S_IXOTH)))
        printf("*");
}

static time_t
get_file_time(const FileInfo *info, const Options *options)
{
    switch (options->time_mode) {
    case TIME_CTIME:
        return info->st.st_ctime;

    case TIME_ATIME:
        return info->st.st_atime;

    case TIME_MTIME:
    default:
        return info->st.st_mtime;
    }
}

/*
 * Print a filename according to -q / -w.
 *
 * -q: non-printable characters become '?'
 * -w: print the filename unchanged
 *
 * Without either option:
 *   terminal     -> behave like -q
 *   non-terminal -> behave like -w
 */
static void
print_name(const char *name, const Options *options)
{
    int use_question;
    const unsigned char *p;

    if (options->name_mode == NAME_QUESTION) {
        use_question = 1;

  } else if (options->name_mode == NAME_RAW) {
        use_question = 0;
    } else {
        use_question = isatty(STDOUT_FILENO);
    }

    if (!use_question) {
        printf("%s", name);
        return;
    }

    p = (const unsigned char *)name;

    while (*p != '\0') {
        if (isprint(*p))
            putchar(*p);
        else
            putchar('?');

        p++;
    }
}

static void
display_long(const FileInfo *info, const Options *options)
{
    struct passwd *pw;
    struct group *gr;
    char timebuf[64];
    char linkbuf[1024];
    ssize_t linklen;
    struct tm *tm_info;
    time_t file_time;

    print_mode(info->st.st_mode);

    printf(" %lu", (unsigned long)info->st.st_nlink);

    if (options->numeric_ids) {
        printf(" %u", (unsigned int)info->st.st_uid);
        printf(" %u", (unsigned int)info->st.st_gid);
    } else {
        pw = getpwuid(info->st.st_uid);
        gr = getgrgid(info->st.st_gid);

        if (pw != NULL)
            printf(" %s", pw->pw_name);
        else
            printf(" %u", (unsigned int)info->st.st_uid);

        if (gr != NULL)
            printf(" %s", gr->gr_name);
        else
            printf(" %u", (unsigned int)info->st.st_gid);
    }

    printf(" ");

    if (options->size_mode == SIZE_HUMAN)
        print_size((long long)info->st.st_size, options);
    else
        printf("%lld", (long long)info->st.st_size);

    file_time = get_file_time(info, options);
    tm_info = localtime(&file_time);

    if (tm_info != NULL) {
        strftime(timebuf, sizeof(timebuf),
            "%b %e %H:%M", tm_info);
        printf(" %s", timebuf);
    }

    printf(" ");
    print_name(info->path, options);
    if (S_ISLNK(info->st.st_mode)) {
        linklen = readlink(info->path, linkbuf,
            sizeof(linkbuf) - 1);

        if (linklen >= 0) {
            linkbuf[linklen] = '\0';
            printf(" -> %s", linkbuf);
        }
    }

    if (options->classify)
        print_classification(info);

    printf("\n");
}

void
display_file(const FileInfo *info, const Options *options)
{
    if (options->inode)
        printf("%lu ", (unsigned long)info->st.st_ino);

    if (options->blocks) {
        long long blocks;

        blocks = (long long)info->st.st_blocks;

        if (options->size_mode == SIZE_KB)
            blocks = (blocks + 1) / 2;

        printf("%lld ", blocks);
    }

    if (options->long_format) {
        display_long(info, options);
    } else if (options->blocks &&
        options->size_mode == SIZE_HUMAN) {

        print_size((long long)info->st.st_size, options);
        printf(" ");
        print_name(info->path, options);

        if (options->classify)
            print_classification(info);

        printf("\n");
    } else {
        print_name(info->path, options);

        if (options->classify)
            print_classification(info);

        printf("\n");
    }
}
