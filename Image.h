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

#endif //CG2_IMAGE_H
