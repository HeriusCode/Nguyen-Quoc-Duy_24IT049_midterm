#ifndef FILEINFO_H
#define FILEINFO_H

#include <sys/types.h>
#include <sys/stat.h>

typedef struct {
    char path[1024];

    struct stat st;

} FileInfo;

int fileinfo_load(const char *path, FileInfo *info);

#endif
