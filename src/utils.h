#ifndef UTILS_H
#define UTILS_H

/* MODES */

#define MODE_OPEN_IMMEDIATELY (1)
#define MODE_SAVE_TO_FILE  (2)
#define MODE_RETURN_TERMINAL (3)

int running_from_term();
void app_to_open(char* path);
void open_app(const int mode);

int get_config_path(char* path);

void dump_debug(const char* str);

#endif
