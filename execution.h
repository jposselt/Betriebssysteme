//
// Created by jonas on 15.05.18.
//

#ifndef BETRIEBSSYSTEME_EXECUTION_H
#define BETRIEBSSYSTEME_EXECUTION_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

#include "builtin.h"

int exec_cmd(char **args);

int fork_shell(char **args);

#endif //BETRIEBSSYSTEME_EXECUTION_H
