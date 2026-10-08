#ifndef OPTIONS_H
#define OPTIONS_H

typedef enum {
    SIZE_DEFAULT,
    SIZE_KB,
    SIZE_HUMAN
} SizeMode;

typedef enum {
    TIME_MTIME,
    TIME_ATIME,
    TIME_CTIME
} TimeMode;

typedef enum {
    SORT_NAME,
    SORT_NONE,
    SORT_SIZE,
    SORT_TIME
} SortMode;

typedef enum {
    NAME_DEFAULT,
    NAME_QUESTION,
    NAME_RAW
} NameMode;

typedef struct {
    int all;
    int almost_all;
    int directory_only;
    int classify;
    int long_format;
    int numeric_ids;
    int inode;
    int blocks;
    int recursive;
    int reverse;
    int summary;

    SizeMode size_mode;
    TimeMode time_mode;
    SortMode sort_mode;
    NameMode name_mode;
} Options;

void options_init(Options *options);
int parse_options(int argc, char **argv, Options *options);

#endif
