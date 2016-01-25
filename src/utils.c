#include <unistd.h>
#include "utils.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char* _app_to_open_path;
#define SHELL "/bin/sh"
void open_app()
{
    if (_app_to_open_path) {

        int status;
        pid_t pid;
        pid = fork ();
        if (pid == 0)
        {
            /* This is the child process.  Execute the shell command. */
            // printf("CHILD\n");

            execl (SHELL, SHELL, "-c", _app_to_open_path, NULL);
        }
        else if (pid < 0)
        /* The fork failed.  Report failure.  */
        status = -1;
        else {
            // parent
            // printf ("PARENT\n");
            // _exit(0);
        }
        // execl (SHELL, SHELL, "-c", _app_to_open_path, NULL);
        // _exit (EXIT_FAILURE);
        // char* c  = popen(_app_to_open_path, "r");
        // system(_app_to_open_path);
        // execve(_app_to_open_path, "", "");
        // printf("%s\n", c);
        // fputs("/usr/lib/firefox/firefox", stdout);
        // fflush(stdout);
		// exit(EXIT_SUCCESS);
    }
}

void
app_to_open(char* path)
{
    _app_to_open_path = path;
}

int
running_from_term()
{
    return isatty(0);
}
