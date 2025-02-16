/**
 * File: lab.c
 * Author: MTumir
 * Created: 02.11.2025
 * Latest: 02.11.2025
 * 
 * Description: Implements functions defined in lab.h.
 */

#include "lab.h"
#include <stdio.h>
#include "readline/readline.h"
#include "readline/history.h"

char *get_prompt(const char *env) {

    return NULL;

}

int change_dir(char **dir) {

    return -1;

}

char **cmd_parse(char const *line) {

    return NULL;

}

void cmd_free(char ** line) {



}

char *trim_white(char *line) {

    return NULL;

}

bool do_builtin(struct shell *sh, char **argv) {

    return false;

}

void sh_init(struct shell *sh) {



}

void sh_destroy(struct shell *sh) {



}

void parse_args(int argc, char **argv) {

    int c;
    while ((c = getopt(argc, argv, "v")) != -1)
    switch (c)
    {
      case 'v':
        printf("CS452-P2: Version %d.%d\n", lab_VERSION_MAJOR, lab_VERSION_MINOR);
        exit(0);
      default:
        printf("Invalid command found, exiting.\n");
        exit(1);
    }

}