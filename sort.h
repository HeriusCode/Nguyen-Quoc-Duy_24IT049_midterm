#ifndef SORT_H
#define SORT_H

#include <stddef.h>

#include "fileinfo.h"
#include "options.h"

typedef struct {
    FileInfo *items;
    size_t count;
} FileList;

void sort_files(FileList *list, const Options *options);

#endif
