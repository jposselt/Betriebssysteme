//
// Created by jonas on 15.05.18.
//

#include "execution.h"

/**
 * Kommando ausführen
 * @param args
 * @return
 */
int exec_cmd(char **args)
{
    if (args[0] == NULL) {
        // kein Kommando
        return 1;
    }

    //...
    return 1;
}

/**
 *
 * @param args
 * @return
 */
int fork_shell(char **args)
{
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