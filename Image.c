#include "Image.h"
#include "Color.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION

#include "stb_image_write.h"
#include "stb_image.h"

/**
 * Função que cria uma imagem
 * @param h
 * @param w
 * @return
 */
Image newImage(int h, int w)
{
    Image img = {h, w, (Color*) malloc(h*w*sizeof(Color))};
    return img;
}

/**
 * Função que libera o campo data alocado para a imagem
 * @param img
 */
void freeImage(Image img)
{
    free(img.data);
}

/**
 * Função que carrega uma imagem
 * @param filename
 * @return
 */
Image loadImage(const char *filename)
{
    int width, height, nrChannels;

    Byte *data = stbi_load(filename, &width, &height, &nrChannels, 0);

    Image img = newImage(height, width);

    for (int i = 0, j = 0; i < (img.w*img.h); i++, j+=3)
    {
        img.data[i].r = data[j];
        img.data[i].g = data[j+1];
        img.data[i].b = data[j+2];
    }

    return img;
}

/**
 * Função que inicializa a imagem com uma cor passada por parametro
 * @param img
 * @param color
 */
void initImage(Image img, Color color)
{
    drawRetangulo(img, color, 0, 0, img.w, img.h);
}

/**
 * Função que salva uma imagem
 * @param filename
 * @param img
 */
void savePng(const char *filename, Image img)
{
    stbi_write_png(filename, img.w, img.h, 3, img.data, 0);
}

/**
 * Função que retorna um ponteiro para a cor de um pixel da imagem
 * @param img
 * @param x
 * @param y
 * @return
 */
Color *pixel(Image img, int x, int y)
{
    return img.data + (img.w*y+x);
}

/**
 * Função que desenha um retangulo na imagem
 * @param img
 * @param color
 * @param x1
 * @param y1
 * @param x2
 * @param y2
 */
void drawRetangulo(Image img, Color color, int x1, int y1, int x2, int y2)
{
    for (int i = x1; i < x2; i++)
        for (int j = y1; j < y2; j++)
            pintar(img, color, i, j);
}

/**
 * Função que pinta um pixel da imagem
 * @param img
 * @param color
 * @param x
 * @param y
 */
void pintar(Image img, Color color, int x, int y)
{
    Color *p = pixel(img, x, y);
    *p = color;
}

/**
 * Função que aplica o filtro luminancia a uma imagem
 * @param img
 * @return
 */
Image luminancia(Image img)
{
    Image imgl = newImage(img.h, img.w);

    for (int i = 0; i < img.w*img.h; i++)
    {
        float r = (float) 0.176*img.data[i].r;
        float g = (float) 0.810*img.data[i].g;
        float b = (float) 0.011*img.data[i].b;

        Byte v = clamp(r+g+b, 0, 255);

        imgl.data[i].r = v;
        imgl.data[i].g = v;
        imgl.data[i].b = v;
    }

    return imgl;
}

/**
 * Função que retorna uma nova imagem que é combinacao de outras duas
 * @param A
 * @param B
 * @param t
 * @return
 */
Image combinacaoImg(Image A, Image B, float t)
{
    Image img = newImage(A.h, B.h);

    for (int i = 0; i < A.h; i++)
    {
        for (int j = 0; j < A.w; j++)
        {
            pintar(img, lerp(t, *pixel(A, i, j), *pixel(B, i, j)), i, j);
        }
    }

    return img;
}