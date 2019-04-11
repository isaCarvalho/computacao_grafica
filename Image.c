#include "Image.h"
#include "Color.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION

#include "stb_image_write.h"
#include "stb_image.h"

int modulo(int x)
{
    return x < 0 ? x*(-1) : x;
}

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
    stbi_flip_vertically_on_write(1);

    stbi_write_png(filename, img.w, img.h, 3, img.data, 0);
}

int max(int a, int b)
{
    return a > b ? a : b;
}

int min(int a, int b)
{
    return a < b ? a : b;
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
        {
            Ponto p = {i, j};
            pintar(img, color, p);
        }
}

/**
 * Função que pinta um pixel da imagem
 * @param img
 * @param color
 * @param x
 * @paragm y
 */

void drawFunction(Image img, Color color, int funcao(int, int))
{
    for (int i = 0; i < img.w; i++)
        for (int j = 0; j < img.h; j++)
            if (funcao(i, j) <= 0)
            {
                Ponto p = {i, j};
                pintar(img, color, p);
            }
}

void pintar(Image img, Color color, Ponto p)
{
    Color *px = pixel(img, p.x, p.y);
    *px = color;
}

void draw_line(Image img, Color color, Ponto p0, Ponto p1)
{

    float m = (float) modulo(p1.y - p0.y) / modulo(p1.x - p0.x);
    int dx = modulo(p1.x - p0.x);
    int dy = modulo(p1.y - p0.y);

    // Reta horizontal
    if (p0.y == p1.y)
    {
        if (p0.x > p1.x)
        {
            Ponto aux = p0;
            p0 = p1;
            p1 = aux;
        }

        for (int i = p0.x; i <= p1.x; i++)
        {
            Ponto p = {i, p0.y};
            pintar(img, color, p);
        }
    }

    // Reta vertical
    else if (p0.x == p1.x)
    {
        if (p0.y > p1.y)
        {
            Ponto aux = p0;
            p0 = p1;
            p1 = aux;
        }

        for (int i = p0.y; i <= p1.y; i++)
        {
            Ponto p = {p0.x, i};
            pintar(img, color, p);
        }
    }

    // Reta y = +-x;
    else if (modulo(p1.x - p0.x) == modulo(p1.y - p0.y))
    {
        for (int i = p0.x, j = p0.y; i <= p1.x; i++)
        {
            Ponto p = {i, j};
            pintar(img, color, p);

            if (p0.y >= p1.y)
                j--;
            else
                j++;
        }
    }

    // modulo 0 < m < 1
    else if (m < 1)
    {
        if (p0.x > p1.x)
        {
            Ponto aux = p0;
            p0 = p1;
            p1 = aux;
        }

        int D = 2*dy - dx;

        int y = p0.y;

        for (int i = p0.x; i <= p1.x; i++)
        {
            Ponto p = {i, y};
            pintar(img, color, p);

            if (D > 0)
            {
                if (p0.y >= p1.y)
                    y--;
                else
                    y++;

                D -= 2*dx;
            }
            D += 2*dy;
        }
    }
    else
    {
        if (p0.y > p1.y)
        {
            Ponto aux = p0;
            p0 = p1;
            p1 = aux;
        }

        int D = 2*dx - dy;

        int x = p0.x;

        for (int i = p0.y; i <= p1.y; i++)
        {
            Ponto p = {x, i};
            pintar(img, color, p);

            if (D > 0)
            {
                if (p0.x >= p1.x)
                    x--;
                else
                    x++;

                D -= 2*dy;
            }
            D += 2*dx;
        }
    }
}

void draw_lines(Image img, Color color, Ponto *p, int n)
{
    for (int i = 0; i < n-1; i += 2)
    {
        draw_line(img, color, p[i], p[i + 1]);
    }
}

void draw_line_strip(Image img, Color color, Ponto *p, int n)
{
    for (int i = 0; i < n-1; i++)
    {
        draw_line(img, color, p[i], p[i + 1]);
    }
}

void draw_line_loop(Image img, Color color, Ponto *p, int n)
{
    draw_line_strip(img, color, p, n);
    draw_line(img, color, p[n-1], p[0]);
}

void draw_elements_lines(Image img, Color color, Ponto *p, const int *indices, int n)
{
    for (int i = 0; i < (n-1); i+=2)
        draw_line(img, color, p[indices[i]], p[indices[i+1]]);
}

void draw_elements_line_strip(Image img, Color color, Ponto *p, const int *indices, int n)
{
    for (int i = 0; i < (n-1); i++)
        draw_line(img, color, p[indices[i]], p[indices[i+1]]);
}

void draw_elements_line_loop(Image img, Color color, Ponto *p, const int *indices, int n)
{
    draw_elements_line_strip(img, color, p, indices, n);
    draw_line(img, color, p[indices[n-1]], p[indices[0]]);
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
            Ponto p = {i, j};
            pintar(img, lerp(t, *pixel(A, i, j), *pixel(B, i, j)), p);
        }
    }

    return img;
}