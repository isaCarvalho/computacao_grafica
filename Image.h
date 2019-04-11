#ifndef CG2_IMAGE_H
#define CG2_IMAGE_H

typedef struct Image
{
    int w, h;
    struct Color *data;
} Image;

typedef struct ponto
{
    float x, y;
} Ponto;

Image newImage(int h, int w);

void freeImage(Image img);

Image loadImage(const char *filename);

void initImage(Image img, struct Color color);

void savePng(const char *filename, Image img);

struct Color *pixel(Image img, float x, float y);

Image luminancia(Image img);

Image combinacaoImg(Image A, Image B, float t);

void draw_pixel(Image img, struct Color color, Ponto p);

void draw_rectangle(Image img, struct Color color, int x1, int y1, int x2, int y2);

void draw_function(Image img, struct Color color, int funcao(int, int));

void draw_line(Image img, struct Color color, Ponto p0, Ponto p1);

void draw_lines(Image img, struct Color color, Ponto *p, int n);

void draw_line_strip(Image img, struct Color color, Ponto *p, int n);

void draw_line_loop(Image img, struct Color color, Ponto *p, int n);

void draw_elements_lines(Image img, struct Color color, Ponto *p, const int *indices, int n);

void draw_elements_line_strip(Image img, struct Color color, Ponto *p, const int *indices, int n);

void draw_elements_line_loop(Image img, struct Color color, Ponto *p, const int *indices, int n);

void draw_circle(Image img, struct Color color, int xc, int yc, int R);

void draw_triangle(Image img, struct Color color, Ponto *p);

void draw_triangles(Image img, struct Color color, Ponto *p, int n);

void draw_triangle_strip(Image img, struct Color color, Ponto *p, int n);

void draw_triangle_fan(Image img, struct Color color, Ponto *p, int n);

void barycentric(Ponto p, Ponto *t, float *b);

#endif //CG2_IMAGE_H
