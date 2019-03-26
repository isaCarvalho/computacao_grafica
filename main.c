#include <stdio.h>
#include "Image.h"
#include "Color.h"

int main()
{
    Image img = newImage(800, 800);

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

    freeImage(img);

    return 0;
}
