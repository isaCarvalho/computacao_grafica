#ifndef CG2_IMAGE_H
#define CG2_IMAGE_H

typedef struct Image
{
    int h, w;
    struct Color *data;
} Image;

typedef struct ponto
{
    int x, y;
} Ponto;

Image newImage(int h, int w);

void freeImage(Image img);

Image loadImage(const char *filename);

void initImage(Image img, struct Color color);

struct Color *pixel(Image img, int x, int y);

void savePng(const char *filename, Image img);

void drawRetangulo(Image img, struct Color color, int x1, int y1, int x2, int y2);

void drawFunction(Image img, struct Color color, int funcao(int, int));

void draw_line(Image img, struct Color color, Ponto p0, Ponto p1);

void draw_lines(Image img, struct Color color, Ponto *p, int n);

void draw_line_strip(Image img, struct Color color, Ponto *p, int n);

void draw_line_loop(Image img, struct Color color, Ponto *p, int n);

void draw_elements_lines(Image img, struct Color color, Ponto *p, const int *indices, int n);

void draw_elements_line_strip(Image img, struct Color color, Ponto *p, const int *indices, int n);

void draw_elements_line_loop(Image img, struct Color color, Ponto *p, const int *indices, int n);

void pintar(Image img, struct Color color, Ponto p);

Image luminancia(Image img);

Image combinacaoImg(Image A, Image B, float t);

#endif //CG2_IMAGE_H
