/**
 * File: lab.c
 * Author: MTumir
 * Created: 02.11.2025
 * Latest: 02.25.2025
 * 
 * Description: Implements functions defined in lab.h.
 */

#include "lab.h"
#include <pwd.h>
#include "readline/readline.h"
#include "readline/history.h"

char *get_prompt(const char *env) {

    char *prompt = getenv(env);
    if (!prompt) {
        return strdup("shell>");
    } return strdup(prompt);

}

int change_dir(char **dir) {

    // If no args are provided
    if (!dir[1] && !chdir(getenv("HOME"))) {
        uid_t user_id = getuid();
        struct passwd *user_pwd = getpwuid(user_id);
        if (!chdir(getenv(user_pwd->pw_dir))) {
            fprintf(stderr, "change_dir failed!\n");
            return 1;
        }
    } 
    // If args are provided
    else {
        chdir(dir[1]);
    }

    return 0;

}

char **cmd_parse(char const *line) {

    char **cmdArray = (char **)malloc(64 * sizeof(char *));
    char *lineCopy = strdup(line);
    char *token = strtok(lineCopy, " ");
    
    // Add tokens to cmdArray, delimited by space
    int i = 0;
    while (token != NULL) {
        cmdArray[i++] = token;
        token = strtok(NULL, " ");
    }

    return cmdArray;

}

void cmd_free(char ** line) {

    for (size_t i = 0; !line[i]; i ++) {
        free(line[i]);
    }
    free(*line);

}

char *trim_white(char *line) {

    // Remove front whitespace
    while (isspace(line[0])) {
        line++;
    }

    // Remove back whitespace
    char *tail = line + strlen(line) - 1;
    while (isspace(tail[0])) {
        tail--;
    }
    tail[1] = '\0';     // Add null char

    return line;

}

bool do_builtin(struct shell *sh, char **argv) {

    char *command = argv[0];

    if (strcmp(command, "exit") == 0) {
        sh_destroy(sh);
        exit(0);
    } if (strcmp(command, "cd") == 0) {
        change_dir(argv);
        return true;
    } if (strcmp(command, "history") == 0) {

        return true;
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