#ifndef CG2_IMAGE_H
#define CG2_IMAGE_H

#include "Mathematics.h"

typedef struct Image
{
    int w, h;
    struct Color *data;

    float* ZBuffer;
    bool useZBuffer;
} Image;

Image newImage(int w, int h, bool useZBuffer = false);

Image loadImage(const char *filename);

Image luminancia(Image);

Image combinacaoImg(Image, Image, float t);

Image xadrez(Image img);

Image imagemBonitinha(Image img);

float* zbuffer(Image img, int x, int y);

struct Color *pixel(Image, float x, float y);

vec3 toScreen(Image img, vec4 P);

void initZBuffer(Image img);

void initImage(Image, struct Color);

void freeImage(Image);

void savePng(const char *filename, Image);

void draw_pixel(Image, struct Color, vec2);

void draw_rectangle(Image, struct Color, int x1, int y1, int x2, int y2);

void draw_function(Image, struct Color, int fn(int, int));

unsigned char code(float x, float y, float xmin, float xmax, float ymin, float ymax);

void draw_line(Image, struct Color, vec2 p0, vec2 p1, float z0 = 0, float z1 = 0);

void draw_line_aux(Image img, Color color, vec2 p0, vec2 p1, float z0 = 0, float z1 = 0);

void draw_lines(Image, struct Color, vec2 *, int n);

void draw_line_strip(Image, struct Color, vec2 *, int n);

void draw_line_loop(Image, struct Color, vec2 *, int n);

void draw_elements_lines(Image, struct Color, vec2 *, const int *i, int n);

void draw_elements_line_strip(Image, struct Color, vec2 *, const int *i, int n);

void draw_elements_line_loop(Image, struct Color, vec2 *, const int *i, int n);

void draw_circle(Image, struct Color, int xc, int yc, int R);

void draw_triangle_bonitinho(Image, struct Color *, vec2 *);

void draw_triangle(Image, struct Color *, vec2 *);

void draw_triangles(Image, struct Color *, vec2 *, int n);

void draw_triangle_strip(Image, struct Color *, vec2 *, int n);

void draw_triangle_fan(Image, struct Color *, vec2 *, int n);

void draw_elements_triangles(Image, struct Color *, vec2 *, const int *i, int n);

void draw_bezier_splines(Image img, struct Color c, vec2 *p, int n);

void draw_line(Image img, Color color, vec4 A, vec4 B);

void draw_lines(Image img, Color color, vec4 *p, int n);

void draw_line_strip(Image img, Color color, vec4 *p, int n);

void draw_line_loop(Image img, Color color, vec4 *p, int n);

void draw_elements_lines(Image img, Color color, vec4 *p, const int *indices, int n);

void draw_elements_line_strip(Image img, Color color, vec4 *p, const int *indices, int n);

void draw_elements_line_loop(Image img, Color color, vec4 *p, const int *indices, int n);

void draw_triangle(Image img, Color C[3], vec4 P[3]);

void draw_triangles(Image img, Color *color, vec4 *p, int n);

void draw_triangle_strip(Image img, Color *color, vec4 *p, int n);

void draw_triangle_fan(Image img, Color *c, vec4 *p, int n);

void draw_elements_triangles(Image img, struct Color *c, vec4 *p, const int *indices, int n);

void draw_wireframe(Image img, Color color, mat4 M, int m, int n, float u0, float u1, float v0, float v1);

void draw_model(Image img, Color *color, mat4 M,vec4 (*f)(float, float), int m, int n, float u0, float u1, float v0, float v1);

#endif //CG2_IMAGE_H
