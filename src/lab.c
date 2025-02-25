/**
 * File: lab.c
 * Author: MTumir
 * Created: 02.11.2025
 * Latest: 02.25.2025
 * 
 * Description: Implements functions defined in lab.h.
 */

#include "lab.h"
#include <stdio.h>
#include "readline/readline.h"
#include "readline/history.h"

char *get_prompt(const char *env) {

    char *prompt = getenv(env);
    if (!prompt) {
        return strdup("shell>");
    } return strdup(prompt);

}

int change_dir(char **dir) {

    return -1;

}

char **cmd_parse(char const *line) {

    // TODO limit length to sysconf

    // char *line = readline("Enter something: ");
    // long max = sysconf("ARGMAX");

    // // TODO change 3
    char **cmdArray = (char **)malloc(3 * sizeof(char *));
    
    cmdArray[0] = (char *)malloc(20 * sizeof(char));
    strcpy(cmdArray[0], line);

    return cmdArray;

}

void cmd_free(char ** line) {

    free(*line); // TODO iterate thru string array

}

char *trim_white(char *line) {

    return line;

}

bool do_builtin(struct shell *sh, char **argv) {

    char *command = argv[0];

    if (strcmp(command, "exit") == 0) {
        sh_destroy(sh);
        exit(0);
    } if (strcmp(command, "cd")) {

    } if (strcmp(command, "history")) {

    }

    return false;

}

void sh_init(struct shell *sh) {

    sh->shell_terminal = STDIN_FILENO;
    sh->shell_is_interactive = isatty(sh->shell_terminal);
    sh->prompt = get_prompt("MY_PROMPT");

}

void sh_destroy(struct shell *sh) {

    free(sh->prompt);

}

void parse_args(int argc, char **argv) {

    int opt;
    while ((opt = getopt(argc, argv, "v")) != -1) {
        switch (opt) {
          case 'v':
            printf("CS452-P2: Version %d.%d\n", lab_VERSION_MAJOR, lab_VERSION_MINOR);
            exit(0);
          default:
            printf("Invalid command found, exiting.\n");
            exit(1);
        }
    }

}