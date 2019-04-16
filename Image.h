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

Image newImage(int w, int h);

void freeImage(Image);

Image loadImage(const char *filename);

void initImage(Image, struct Color);

void savePng(const char *filename, Image);

struct Color *pixel(Image, float x, float y);

Image luminancia(Image);

Image combinacaoImg(Image, Image, float t);

void draw_pixel(Image, struct Color, Ponto);

void draw_rectangle(Image, struct Color, int x1, int y1, int x2, int y2);

void draw_function(Image, struct Color, int fn(int, int));

void draw_line(Image, struct Color, Ponto p0, Ponto p1);

void draw_lines(Image, struct Color, Ponto *, int n);

void draw_line_strip(Image, struct Color, Ponto *, int n);

void draw_line_loop(Image, struct Color, Ponto *, int n);

void draw_elements_lines(Image, struct Color, Ponto *, const int *i, int n);

void draw_elements_line_strip(Image, struct Color, Ponto *, const int *i, int n);

void draw_elements_line_loop(Image, struct Color, Ponto *, const int *i, int n);

void draw_circle(Image, struct Color, int xc, int yc, int R);

void draw_triangle_bonitinho(Image, struct Color *, Ponto *);

void draw_triangle(Image, struct Color *, Ponto *);

void draw_triangles(Image, struct Color *, Ponto *, int n);

void draw_triangle_strip(Image, struct Color *, Ponto *, int n);

void draw_triangle_fan(Image, struct Color *, Ponto *, int n);

void draw_elements_triangles(Image, struct Color *, Ponto *, const int *i, int n);

#endif //CG2_IMAGE_H
