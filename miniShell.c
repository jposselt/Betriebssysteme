// Compile gcc -o minishell miniShell.c

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include "input.h"
#include "execution.h"
#include "builtin.h"

/**
 * Prompt anzeigen
 */
void print_prompt(void) {
    printf("%s:%s$ ", getlogin(), getcwd(0, 0));
}

/**
 * Hauptschleife
 */
void shell_loop(void) {
    char *line;
    char **args;
    int status;

    do {
        print_prompt();
        line = read_line();
        args = parse_line(line);
        status = exec_cmd(args);

        // Speicher freigeben
        free(line);
        free(args);
    } while (status);
}

/**
 * Main
 * @param argc
 * @param argv
 * @return EXIT_SUCCESS oder EXIT_FAILURE
 */
int main(int argc, const char *argv[]) {

    // Hauptschleife
    shell_loop();

    return EXIT_SUCCESS;
}
