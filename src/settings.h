#ifndef SETTINGS_H
#define SETTINGS_H

#include <glib.h>
#include "utils_string.h"

#define CONFIG_FILE "default.conf"

// [Main]
// dirs = $PATH, $MYPATH, /home/lchsk/
// no_gui = true
// executables_only = true
// 
// [Aliases]
// aliases = true
// aliases_filenames = .bashrc, .zshrc
// 
// [Cache]
// cache = true
// cache_refresh = 24
// 
// [Search]
// search_from_start_only = false
// ignore_case = true
// allow_regexp = false
// adjust_by_use = true


typedef struct {
	int mode;
	int help;
} cmdline_t;

typedef struct {
    str_array_t* dirs;
	gchar* terminal;
    int executables_only;
} config_main_t;

typedef struct {
    config_main_t* section_main;
} config_t;

void load_config();
void free_config();

/* TODO: config should take config_t as argument */
config_t* config();
void read_cmdline(cmdline_t* cmdline, int argc, char** argv);

#endif
