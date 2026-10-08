#include <stdio.h>
#include <unistd.h>

#include "options.h"

void
options_init(Options *options)
{
    options->all = 0;
    options->almost_all = 0;
    options->directory_only = 0;
    options->classify = 0;
    options->long_format = 0;
    options->numeric_ids = 0;
    options->inode = 0;
    options->blocks = 0;
    options->recursive = 0;
    options->reverse = 0;
    options->summary = 0;

    options->size_mode = SIZE_DEFAULT;
    options->time_mode = TIME_MTIME;
    options->sort_mode = SORT_NAME;
    options->name_mode = NAME_DEFAULT;
}

int
parse_options(int argc, char **argv, Options *options)
{
    int opt;

    while ((opt = getopt(argc, argv, "AacdFfhiklnqRrSstuw")) != -1) {
        switch (opt) {
        case 'A':
            options->almost_all = 1;
            break;

        case 'a':
            options->all = 1;
            break;

        case 'c':
            options->time_mode = TIME_CTIME;
            break;

        case 'd':
            options->directory_only = 1;
            break;

        case 'F':
            options->classify = 1;
            break;

        case 'f':
            options->sort_mode = SORT_NONE;
            break;

        case 'h':
            options->size_mode = SIZE_HUMAN;
            break;

        case 'i':
            options->inode = 1;
            break;

        case 'k':
            options->size_mode = SIZE_KB;
            break;

        case 'l':
            options->long_format = 1;
            options->numeric_ids = 0;
            break;

        case 'n':
            options->long_format = 1;
            options->numeric_ids = 1;
            break;

        case 'q':
            options->name_mode = NAME_QUESTION;
            break;

        case 'R':
            options->recursive = 1;
            break;

        case 'r':
            options->reverse = 1;
            break;

        case 'S':
            options->sort_mode = SORT_SIZE;
            break;

        case 's':
            options->blocks = 1;
            break;

        case 't':
            options->sort_mode = SORT_TIME;
            break;

        case 'u':
            options->time_mode = TIME_ATIME;
            break;

        case 'w':
            options->name_mode = NAME_RAW;
            break;

        default:
            fprintf(stderr, "usage: myls [options] [file ...]\n");
            return -1;
        }
    }

    return optind;
}
