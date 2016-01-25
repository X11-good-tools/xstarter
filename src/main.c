#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>

#include <glib.h>

#include "settings.h"
#include "scan.h"
#include "term.h"
#include "utils.h"

#include <menu.h>

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))
#define CTRLD 	4


int main()
{
    // if ( ! running_from_term()) {
    //     system("rxvt-unicode -e /home/lchsk/projects/xstarter/bin/xstarter");
    //     // system("rxvt-unicode -e /home/lchsk/projects/xstarter/bin/xstarter", "w");
    //     return 0;
    // }
    load_config();

    load_cache();

    init_search();

    // search("atom");
    // printf_results();

    init_term_gui();
    run_term();
    free_term_gui();

    free_cache();
    free_search();
    free_config();

    // printf("opening...\n");
    open_app();



  // popen("firefox", "w");
}

