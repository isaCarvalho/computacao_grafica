#ifndef CG2_IMAGE_H
#define CG2_IMAGE_H

typedef struct Image
{
    int h, w;
    struct Color *data;
} Image;

Image newImage(int h, int w);

void freeImage(Image img);

void initImage(Image img, struct Color color);

struct Color *pixel(Image img, int x, int y);

void savePng(const char *filename, Image img);

void drawRetangulo(Image img, struct Color color, int x1, int y1, int x2, int y2);

void pintar(Image img, struct Color color, int x, int y);

#endif //CG2_IMAGE_H
