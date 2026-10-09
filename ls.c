#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <limits.h>

#include "ls.h"
#include "fileinfo.h"
#include "display.h"
#include "sort.h"

static int
should_show(const char *name, const Options *options)
{
    if (name[0] != '.')
        return 1;

    if (options->all)
        return 1;

    if (options->almost_all) {
        if (strcmp(name, ".") == 0 ||
            strcmp(name, "..") == 0)
            return 0;

        return 1;
    }

    return 0;
}

static void
list_file(const char *path, const Options *options)
{
    FileInfo info;

    if (fileinfo_load(path, &info) == 0)
        display_file(&info, options);
}

static void
list_directory(const char *path, const Options *options)
{
    DIR *dir;
    struct dirent *entry;
    char fullpath[PATH_MAX];

    FileList list;
    size_t capacity = 16;

    dir = opendir(path);

    if (dir == NULL) {
        perror(path);
        return;
    }

    list.items = malloc(capacity * sizeof(FileInfo));
    list.count = 0;

    if (list.items == NULL) {
        perror("malloc");
        closedir(dir);
        return;
    }

    while ((entry = readdir(dir)) != NULL) {
        FileInfo info;

        if (!should_show(entry->d_name, options))
            continue;

        if (strcmp(path, ".") == 0) {
            snprintf(fullpath, sizeof(fullpath),
                "./%s", entry->d_name);
        } else {
            snprintf(fullpath, sizeof(fullpath),
                "%s/%s", path, entry->d_name);
        }

        if (fileinfo_load(fullpath, &info) != 0)
            continue;

        if (list.count == capacity) {
            FileInfo *new_items;

            capacity *= 2;

            new_items = realloc(list.items,
                capacity * sizeof(FileInfo));

            if (new_items == NULL) {
                perror("realloc");
                free(list.items);
                closedir(dir);
                return;
            }

            list.items = new_items;
        }

        list.items[list.count] = info;
        list.count++;
    }

    closedir(dir);

    sort_files(&list, options);

    {
        size_t i;

        for (i = 0; i < list.count; i++)
            display_file(&list.items[i], options);
    }

    /*
     * Recursive listing.
     *
     * Use lstat() through fileinfo_load(), so a symbolic
     * link to a directory is not followed as a directory.
     */
    if (options->recursive) {
        size_t i;

        for (i = 0; i < list.count; i++) {
            if (S_ISDIR(list.items[i].st.st_mode)) {
                printf("\n%s:\n", list.items[i].path);
                list_directory(list.items[i].path, options);
            }
        }
    }





































free(list.items);
}
int
ls_path(const char *path, const Options *options)
{
    struct stat st;

    if (lstat(path, &st) == -1) {
        perror(path);
        return -1;
    }

    if (options->directory_only) {
        list_file(path, options);
        return 0;
    }

    if (S_ISDIR(st.st_mode))
        list_directory(path, options);
    else
        list_file(path, options);

    return 0;
}































