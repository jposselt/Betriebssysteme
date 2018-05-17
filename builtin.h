//
// Created by jonas on 15.05.18.
//

#ifndef BETRIEBSSYSTEME_BUILTIN_H
#define BETRIEBSSYSTEME_BUILTIN_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int builtin_exit(char **args);

int builtin_cd(char **args);

int builtin_set(char **args);

int num_builtins();

extern char *builtin_str[];

extern int (*builtin_func[])(char **);

#endif //BETRIEBSSYSTEME_BUILTIN_H
