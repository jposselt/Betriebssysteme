//
// Created by jonas on 15.05.18.
//

#ifndef BETRIEBSSYSTEME_EXECUTION_H
#define BETRIEBSSYSTEME_EXECUTION_H

#include "builtin.h"

int exec_cmd(char **args);

int fork_shell(char **args);

#endif //BETRIEBSSYSTEME_EXECUTION_H
