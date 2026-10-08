#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "fileinfo.h"

int
fileinfo_load(const char *path, FileInfo *info)
{
    if (path == NULL || info == NULL)
        return -1;

    if (strlen(path) >= sizeof(info->path))
        return -1;

    strcpy(info->path, path);

    if (lstat(path, &info->st) == -1) {
        perror(path);
        return -1;
    }

    return 0;
}
