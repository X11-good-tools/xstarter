#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <omp.h>
#include <glib.h>
#include <limits.h>
#include <string.h>

#include "scan.h"
#include "settings.h"
#include "utils_string.h"


static void refresh_cache();

int count = 0;
int PATH = 3000;

static GQueue* search_paths = NULL;

static void
listdir(char* name, int level)
{
    DIR *dir;
    struct dirent *entry;

    if (!(dir = opendir(name)))
        return;
    if (!(entry = readdir(dir)))
        return;

    char buf[PATH + 1];

    do {
        if (entry->d_type == DT_DIR) {
            char path[PATH];
            int len = snprintf(path, sizeof(path)-1, "%s/%s", name, entry->d_name);
            path[len] = 0;

            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
                continue;

            listdir(path, level + 1);
        } else {
            struct stat sb;
            memset(buf, NULL, sizeof(buf));
            strcpy(buf, name);
            strcat(buf, "/");
            strcat(buf, entry->d_name);
            if (stat(buf, &sb) == 0 && sb.st_mode & S_IXUSR) {
                count++;
                g_queue_push_tail(search_paths, strdup(buf));
            }
        }
    } while ((entry = readdir(dir)) != NULL);

    closedir(dir);
}

static void refresh_cache()
{
    GQueue* paths = g_queue_new();

    str_array_t* dirs = config()->section_main->dirs;

    for (int i = 0; i < dirs->length; i++) {
        if (dirs->data[i][0] == '$') {
            char const* var = g_getenv(++dirs->data[i]);

            if (var != NULL) {
                str_array_t* var_paths = str_array_new(strdup(var), ":");

                if (var_paths != NULL) {
                    for (int j = 0; j < var_paths->length; j++) {
                        if (var_paths->data[j] != NULL) {
                            g_queue_push_tail(paths, strdup(var_paths->data[j]));
                        }
                    }
                }

                str_array_free(var_paths);
            }
        } else {
            g_queue_push_tail(paths, (dirs->data[i]));
        }
    }

    search_paths = g_queue_new();

    char* path;
    while ((path = g_queue_pop_head(paths)) != NULL) {
        listdir(path, 0);
    }

    if (paths != NULL)
        g_queue_free(paths);
}

void
load_cache()
{
    #pragma omp parallel sections
    {
        #pragma omp section
        {
            refresh_cache();
        }
    }
}

void free_cache()
{
    if (search_paths != NULL)
        g_queue_free(search_paths);
}

GQueue* get_cache()
{
    return search_paths;
}