//
// Created by jonas on 15.05.18.
//

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <wordexp.h>

#include "execution.h"

/**
 * Kommando ausführen
 * @param args
 * @return 1
 */
int exec_cmd(char **args) {
    int status = 1;
    wordexp_t result;

    if (args[0] == NULL) {
        // kein Kommando
        return status;
    }

    // Expandiere Kommando
    switch (wordexp(args[0], &result, 0)) {
        case 0:                     /* Erfolgreich  */
            break;
        case WRDE_NOSPACE:          /* Nicht genug Speicher */
            perror("minishell");
            exit(EXIT_FAILURE);
        default:                    /* Anderer Fehler  */
            perror("minishell");
            return status;
    }

    // Expandiere Argumente
    for (int i = 1; args[i] != NULL; i++) {
        if (wordexp(args[i], &result, WRDE_APPEND)) {
            perror("minishell");
            wordfree(&result);
            return status;
        }
    }

    // Builtin Kommando
    for (int i = 0; i < num_builtins(); i++) {
        if (strcmp(result.we_wordv[0], builtin_str[i]) == 0) {
            status = (*builtin_func[i])(result.we_wordv);
            wordfree(&result);
            return status;
        }
    }

    // alle anderen Kommandos
    status = fork_shell(result.we_wordv);
    wordfree(&result);
    return status;
}

/**
 *
 * @param args
 * @return 1
 */
int fork_shell(char **args) {
    pid_t pid;
    int status;

    pid = fork();
    if (pid == 0) {
        // Kindprozess
        if (execvp(args[0], args) == -1) {
            perror("minishell");
        }
        exit(EXIT_FAILURE);
    } else if (pid < 0) {
        // Fehler beim Forken
        perror("minishell");
    } else {
        // Elternprozess
        do {
            waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }

    return 1;
}