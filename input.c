//
// Created by jonas on 15.05.18.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "input.h"

#define TOKEN_BUFSIZE 64
#define TOKEN_DELIM " \t\r\n\a"

/**
 * Einlesen einer Zeile von der Standardeingabe
 * @return Eingelesene Zeile (Freigabe durch Benutzer)
 */
char *read_line(void) {
    char *line = NULL;
    ssize_t bufsize = 0; // getline alloziert Buffer
    if(getline(&line, &bufsize, stdin) == -1) {
        perror("minishell");
        exit(EXIT_FAILURE);
    }
    return line;
}

/**
 * Parsen der Eingabe
 * @param line Befehlsstring (Kommando + Argumente)
 * @return Array mit dem Befehl und den einzelnen Argumenten (Freigabe durch Benutzer)
 */
char **parse_line(char *line) {
    int bufsize = TOKEN_BUFSIZE;
    int position = 0;
    char **tokens = malloc(bufsize * sizeof(char *));
    char *token;

    if (!tokens) {
        fprintf(stderr, "minishell: allocation error\n");
        exit(EXIT_FAILURE);
    }

    token = strtok(line, TOKEN_DELIM);
    while (token != NULL) {
        tokens[position] = token;
        position++;

        if (position >= bufsize) {
            bufsize += TOKEN_BUFSIZE;
            tokens = realloc(tokens, bufsize * sizeof(char *));
            if (!tokens) {
                fprintf(stderr, "minishell: allocation error\n");
                exit(EXIT_FAILURE);
            }
        }

        token = strtok(NULL, TOKEN_DELIM);
    }
    tokens[position] = NULL;
    return tokens;
}