//
// Created by jonas on 15.05.18.
//
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include "builtin.h"

// Liste der Builtin-Kommandos
char *builtin_str[] = {
        "exit",
        "cd",
        "set"
};

// Zeigerarray auf Builtin-Kommandos
int (*builtin_func[])(char **) = {
        &builtin_exit,
        &builtin_cd,
        &builtin_set
};

/**
 * Hilfsfunktion
 * @return Anzahl der Builtin-Kommandos
 */
int num_builtins() {
    return sizeof(builtin_str) / sizeof(char *);
}

/**
 * Builtin Kommando zum Beenden der Shell
 * @param args ohne Funktion
 * @return 0
 */
int builtin_exit(char **args) {
    return 0;
}

/**
 * Builtin Kommando zum Wechseln des Arbeitsverzeichnisses
 * @param args Array (cd-Kommando + Argumente); nur das erste Argument wird berücksichtigt
 * @return 1
 */
int builtin_cd(char **args) {
    if (args[1] == NULL) {
        fprintf(stderr, "minishell: no argument for \"cd\"\n");
    } else {
        if (chdir(args[1]) != 0) {
            perror("minishell");
        }
    }
    return 1;
}

/**
 * Builtin Kommando zum Setzen/Ändern von Umgebungsvariablen
 * @param args Array (set-Kommando + Argumente); nur das erste Argument wird berücksichtigt
 * @return 1
 */
int builtin_set(char **args) {
    if (args[1] == NULL) {
        fprintf(stderr, "minishell: no argument for \"set\"\n");
    } else {
        if (putenv(args[1]) != 0) {
            perror("minishell");
        }
    }
    return 1;
}