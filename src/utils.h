#ifndef UTILS_H
#define UTILS_H

#include <stdbool.h>

#define PRINT(x) { printf("%s\n", x); }

/* MODES */

#define MODE_RETURN_TERMINAL (1)
#define MODE_OPEN_APP (2)

#define RECENT_APPS_REMEMBERED (100)

#define ASCII_0 (48)
#define ASCII_1 (49)
#define ASCII_9 (57)

/* Errors */

#define NO_ERR (0)
#define ERR_UNKNOWN_APP_MODE (1)
#define ERR_NO_XSTARTER_DIR (2)
#define ERR_DIRS_TOO_LONG (3)
#define ERR_XSTARTER_MKDIR_FAILED (4)
#define ERR_FORK_FAILED (5)
#define ERR_SETSID_FAILED (6)
#define ERR_CHDIR_FAILED (7)

void open_app(char *path);

/* Error code */
static int err;

char xstarter_dir[1024];
int xstarter_dir_avail;

char recent_apps[100][1024];
int recent_apps_cnt;

void app_to_open(char *path);

void dump_debug(const char *str);
void dump_debug_ptr(const char *str);
void dump_debug_int(int d);
void dump_debug_char(const char);

void xstarter_directory();

void read_recently_open_list();

void set_err(int err_code);
int get_err();
void print_err();

void *safe_malloc(size_t n, unsigned long line);
#define smalloc(n) safe_malloc(n, __LINE__);

#endif
