#include "Image.h"
#include "Color.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

Image newImage(int h, int w)
{
    Image img = {h, w, (Color*) malloc(h*w*sizeof(Color))};
    return img;
}

void freeImage(Image img)
{
    free(img.data);
}

void initImage(Image img, Color color) {
    drawRetangulo(img, color, 0, 0, img.w, img.h);
}

void savePng(const char *filename, Image img)
{
    stbi_write_png(filename, img.w, img.h, 3, img.data, 0);
}

Color *pixel(Image img, int x, int y)
{
    return img.data + (img.w*y+x);
}

void drawRetangulo(Image img, Color color, int x1, int y1, int x2, int y2)
{
    for (int i = x1; i < x2; i++)
    {
        for (int j = y1; j < y2; j++)
        {
            Color *p = pixel(img, i, j);
            *p = color;
        }
    }
}
