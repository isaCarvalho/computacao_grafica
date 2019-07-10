//
// Created by isabela on 08/07/19.
//

#ifndef CG2_OBJFILE_H
#define CG2_OBJFILE_H

#include "Mathematics.h"
#include "cstring"

FILE *open_file();

void read_file(FILE *arq, int *nvert, int *narest);

vec4 *get_vertices(FILE *arq, int nvert);

vec3 *get_arestas(FILE *arq, int narest);

void close_file(FILE *arq);

#endif //CG2_OBJFILE_H
