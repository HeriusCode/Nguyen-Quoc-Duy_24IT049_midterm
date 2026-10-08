#include <string.h>
#include <time.h>

#include "sort.h"

static int
compare_name(const FileInfo *a, const FileInfo *b)
{
    return strcmp(a->path, b->path);
}

static int
compare_size(const FileInfo *a, const FileInfo *b)
{
    if (a->st.st_size < b->st.st_size)
        return 1;

    if (a->st.st_size > b->st.st_size)
        return -1;

    return compare_name(a, b);
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

static int
compare_time(const FileInfo *a, const FileInfo *b,
    const Options *options)
{
    time_t time_a;
    time_t time_b;

    time_a = get_file_time(a, options);
    time_b = get_file_time(b, options);

    if (time_a < time_b)
        return 1;

    if (time_a > time_b)
        return -1;

    return compare_name(a, b);
}

static int
compare_items(const FileInfo *a, const FileInfo *b,
    const Options *options)
{
    int result;

    switch (options->sort_mode) {
    case SORT_NONE:
        return 0;

    case SORT_SIZE:
        result = compare_size(a, b);
        break;

    case SORT_TIME:
        result = compare_time(a, b, options);
        break;

    case SORT_NAME:
    default:
        result = compare_name(a, b);
        break;
    }

    if (options->reverse)
        return -result;

    return result;
}

void
sort_files(FileList *list, const Options *options)
{
    size_t i;
    size_t j;
    FileInfo temp;

    if (list == NULL || options == NULL)
        return;

    for (i = 0; i < list->count; i++) {
        for (j = i + 1; j < list->count; j++) {
            if (compare_items(&list->items[i],
                &list->items[j], options) > 0) {

                temp = list->items[i];
                list->items[i] = list->items[j];
                list->items[j] = temp;
            }
        }
    }
}
