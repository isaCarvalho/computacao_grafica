#include <cstdio>
#include <cstdlib>
#include <cmath>
#include "Image.h"
#include "Color.h"
#include "objFile.h"
#include "objects.h"
#include <complex>

int main()
{
    // GATINHO
    FILE *arq = open_file();

    int nvert, narest;
    read_file(arq, &nvert, &narest);

    vec4 *vertices = get_vertices(arq, nvert);

    vec3 *arestas = get_arestas(arq, narest);

    int *indices = get_indices(arestas, narest);

    Image img = newImage(800, 800, true);
    initImage(img, {157, 201, 221});

    // CHÃO

    Color cor[4] = {{61, 84, 30}, {0, 255, 0}, {61, 84, 30}, {167, 205, 116}};

    //view
    mat4 View = lookAt({0,0,20}, {0,0,0}, {0,2,0});

    //projection
    float a = (float) img.w/img.h;
    mat4 Projection = perspective(45, a, 10, 1);

    //model
    mat4 Model = scale(4.6, 1, 1) *rotate_x(-2)* translate(0, 0, -10) * rotate_z(0) * rotate_y(0);

    //projection
    mat4 M = Projection*View*Model;

    draw_model(img, cor, M, waves, 30, 30, -6, 6, -6, 6);

    Color cores[] = {{0, 0, 0}, {38, 16, 16}, {0,0,0},{0,0,0}};

    Color *C = get_color_vertices(cores, vertices, nvert);

    //view
    View = lookAt({1,3,8}, {1,0,0}, {0,1,0});

    //projection
    a = (float) img.w/img.h;
    Projection = perspective(45, a, 10, 1);

    //model
    Model = scale(3, 3, 3) * translate(-0.6, -0.6, 0) *rotate_x(-0.60) * rotate_z(0) * rotate_y(0.4);

    //projection
    M = Projection*View*Model;

    vec4 MP2[nvert];

    multMV4(M, vertices, nvert, MP2);

    draw_elements_triangles(img, C, MP2, indices, 3*narest);

    /** SOL*/

    Color cor2[4] = {{248, 193, 52}, {248, 193, 52}, {248, 193, 52}, {248, 193, 52}};

    //    view
    View = lookAt({0,0,20}, {1,0,0}, {0,1,0});

    //projection
    a = (float) img.w/img.h;
    Projection = perspective(45, a, 10, 50);

    //model3306
    Model = scale(1.6, 1.6, 1.6) *rotate_x(-2.3)* translate(4, -3, 4) * rotate_z(-0.50);

    //projection
    M = Projection*View*Model;

    draw_model(img, cor2, M, sphere, 30, 30, -5, 5, -5, 5);

    savePng("gatinho.png", img);
    freeImage(img);

    return 0;
}
