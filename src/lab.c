/**
 * File: lab.c
 * Author: MTumir
 * Created: 02.11.2025
 * Latest: 02.28.2025
 * 
 * Description: Implements functions defined in lab.h.
 */

#include "lab.h"

#include <pwd.h>
#include <signal.h>

#include "readline/readline.h"
#include "readline/history.h"

char *get_prompt(const char *env) {

    char *prompt = getenv(env);
    if (!prompt) {      // CR- If the env variable doesn't exist, revert to default prompt
        return strdup("shell>");
    } return strdup(prompt);

}

int change_dir(char **dir) {

    // CR- If no args are provided, chdir with HOME env variable.
    //      If this fails, get home directory through user_id.
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

/**
 * CR- Prints all previous commands entered into the current shell.
 */
void get_history(void) {

    HIST_ENTRY **list = history_list();
    if (list) {
        for (int i = 0; list[i]; i ++) {
            printf ("%d: %s\n", i + history_base, list[i]->line);
        }
    }

}

char **cmd_parse(char const *line) {

    // CR- Updated cmd_array allocation to use ARG_MAX, as was shown in class
    char **cmd_array = (char**) calloc (sysconf(_SC_ARG_MAX), sizeof(char*));
    char *line_copy = strdup(line);
    char *token = strtok(line_copy, " ");
    
    // Add tokens to cmd_array, delimited by space
    int i = 0;
    while (token) {
        cmd_array[i++] = strdup(token);
        token = strtok(NULL, " ");
    }

    cmd_array[i] = NULL;
    free(line_copy);
    return cmd_array;

}

void cmd_free(char ** line) {

    // CR- Iterate through line, freeing each char *
    for (size_t i = 0; line[i]; i ++) {
        free(line[i]);
    }

    free(line);

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
        get_history();      // CR- Moved history code to function
        return true;
    }

    return false;

}

void sh_init(struct shell *sh) {

    sh->shell_terminal = STDIN_FILENO;
    sh->shell_is_interactive = isatty(sh->shell_terminal);
    sh->prompt = get_prompt("MY_PROMPT");
    // sh->shell_pgid = getpid();   // CR- Commented unnecessary code

    // CR- Added code important to the shell running?
    // CR- While the shell is interactive...
    if(sh->shell_is_interactive){
        // CR- While the ID of the terminal is not equal to the ID of the shell...
        while(tcgetpgrp(sh->shell_terminal) != (sh->shell_pgid = getpgrp()))
            // CR- Stop the shell's process.
            //      https://www.gnu.org/software/libc/manual/html_node/Job-Control-Signals.html
            kill(-sh->shell_pgid, SIGTTIN);
    }

    // Signals to ignore
    signal(SIGINT, SIG_IGN);
    signal(SIGQUIT, SIG_IGN);
    signal(SIGTSTP, SIG_IGN);
    signal(SIGTTIN, SIG_IGN);
    signal(SIGTTOU, SIG_IGN);

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