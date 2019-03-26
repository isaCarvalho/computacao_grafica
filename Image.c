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
    for(int i = 0; i < img.w; i++)
    {
        for(int j = 0; j < img.h; j++)
        {
            Color *p = pixel(img, i, j);
            *p = color;
        }
    }
}

void savePng(const char *filename, Image img)
{
    stbi_write_png(filename, img.w, img.h, 3, img.data, 0);
}

Color *pixel(Image img, int x, int y)
{
    return img.data + (img.w*y+x);
}
