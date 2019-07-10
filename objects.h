#ifndef CG2_OBJECTS_H
#define CG2_OBJECTS_H

#include "Mathematics.h"
#include "Color.h"

Color *get_color_vertices(Color *color, vec4 *vertices, int nvert);

int* get_indices(vec3 *arestas, int narest);

#endif //CG2_OBJECTS_H
