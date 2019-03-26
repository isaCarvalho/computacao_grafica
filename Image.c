#include "Image.h"
#include "Color.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

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
 * Função que inicializa a imagem com uma cor passada por parametro
 * @param img
 * @param color
 */
void initImage(Image img, Color color) {
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
