#include <stdio.h>
#include "Image.h"
#include "Color.h"

void xadrez(Image img)
{
    Color preto = {0, 0, 0};
    Color branco = {255, 255, 255};

    initImage(img, preto);


    for(int j = 0; j < img.h; j += 200)
        for(int i = 0; i < img.w; i += 200)
            drawRetangulo(img, branco, i, j, i+100, j+100);

    for(int j = 100; j < img.h; j += 200)
        for(int i = 100; i < img.w; i += 200)
            drawRetangulo(img, branco, i, j, i+100, j+100);

    savePng("xadrez.png", img);
}

void imagemBonitinha(Image img)
{
    Color A = {255, 0, 0}, B = {0, 255, 0}, C = {0, 0, 255}, D = {255, 0, 255};

    for (int j = 0; j < img.h; j++)
    {
        float v = (float) j/(img.h-1);

        for (int i = 0; i < img.w; i++)
        {
            float u = (float) i/(img.w-1);
            pintar(img, interpolacaoBilinear(u, v, A, B, C, D), i, j);
        }
    }

    savePng("imagemBonitinha.png", img);
}

int main()
{
    Image img = newImage(800, 800);

    xadrez(img);
    imagemBonitinha(img);

    Image img1 = loadImage("imagemBonitinha.png");

    Image img2 = luminancia(img1);

    savePng("luminancia.png", img2);

    freeImage(img2);
    freeImage(img);

    return 0;
}
