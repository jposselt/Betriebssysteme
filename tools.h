//
// Created by jonas on 13.06.18.
//

#ifndef SYNCHRONISATION_TOOLS_H
#define SYNCHRONISATION_TOOLS_H

const char *get_filename_ext(const char *filename);
const char *get_file_content(const char *filename);
int write_file(const char *filename, const char *content);

#endif //SYNCHRONISATION_TOOLS_H
