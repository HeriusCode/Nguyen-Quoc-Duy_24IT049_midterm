
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

#include "options.h"
#include "ls.h"
#include "fileinfo.h"
#include "display.h"
#include "sort.h"

static int
load_operands(int argc, char **argv, int first_operand,
    FileList *files, FileList *directories)
{
    int i;
    int had_error = 0;

    files->items = NULL;
    files->count = 0;
    directories->items = NULL;
    directories->count = 0;

    for (i = first_operand; i < argc; i++) {
        FileInfo info;

        if (fileinfo_load(argv[i], &info) != 0) {
            had_error = 1;
            continue;
        }

        if (S_ISDIR(info.st.st_mode)) {
            FileInfo *new_items;

            new_items = realloc(directories->items,
                (directories->count + 1) * sizeof(FileInfo));

            if (new_items == NULL) {
                perror("realloc");
                free(files->items);
                free(directories->items);
                return -1;
            }

            directories->items = new_items;
            directories->items[directories->count] = info;
            directories->count++;
        } else {
            FileInfo *new_items;

            new_items = realloc(files->items,
                (files->count + 1) * sizeof(FileInfo));

            if (new_items == NULL) {
                perror("realloc");
                free(files->items);
                free(directories->items);
                return -1;
            }

            files->items = new_items;
            files->items[files->count] = info;
            files->count++;
        }
    }

    return had_error;
}

static void
display_operands(FileList *files, FileList *directories,
    const Options *options)
{
    size_t i;

    sort_files(files, options);
    sort_files(directories, options);

    for (i = 0; i < files->count; i++)
        display_file(&files->items[i], options);

    for (i = 0; i < directories->count; i++) {
        if (files->count > 0 || directories->count > 1)
            printf("\n%s:\n", directories->items[i].path);

        (void)ls_path(directories->items[i].path, options);
    }
}

int
main(int argc, char **argv)
{
    Options options;
    int first_operand;
    int operand_status;
    FileList files;
    FileList directories;

    options_init(&options);

    first_operand = parse_options(argc, argv, &options);

    if (first_operand < 0)
        return 1;

    if (first_operand >= argc)
        return ls_path(".", &options) == 0 ? 0 : 1;

    operand_status = load_operands(argc, argv, first_operand,
        &files, &directories);

    if (operand_status < 0)
        return 1;

    display_operands(&files, &directories, &options);

    free(files.items);
    free(directories.items);

    return operand_status == 0 ? 0 : 1;
}

