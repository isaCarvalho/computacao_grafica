#include "objects.h"

Color *get_color_vertices(Color *color, vec4 *vertices, int nvert)
{
    auto *cout = (Color*) malloc(nvert*sizeof(Color));

    for(int i=0; i<nvert; i++){
        cout[i] = interpolacaoBilinear(vertices[i].x, vertices[i].y, color[0], color[1], color[2], color[3]);
    }

    return cout;
}

int* get_indices(vec3 *arestas, int narest)
{
    int* indices = (int*)malloc(6244*sizeof(int));
//    int indices[6243];

    printf("\nnarest = %d\n", 3*narest);

    int k = 0;
    for(int i=0; i< narest; i++)
    {
        indices[k++] = arestas[i].x;
        indices[k++] = arestas[i].y;
        indices[k++] = arestas[i].z;

//        printf("\ni = %d k = %d\n", i, k);
    }
//    printf("REEEEEEEEEEEEEEEELOU %d", k);

    return indices;
}