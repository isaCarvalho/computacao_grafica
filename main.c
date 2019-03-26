#include <stdio.h>
#include "Image.h"
#include "Color.h"

int main()
{
    Image img = newImage(800, 800);

    Color preto = {0, 0, 0};
    Color branco = {255, 255, 255};

    initImage(img, preto);

    int cont = -1, conti = 0, i;

    for (int j = 0; j < img.h; j++, cont++)
    {
        if (cont >= 100 && cont <= 200)
            i = 100;
        else
            i = 0;

        if (cont == 200)
            cont = 0;

        for (; i < img.w; i++, conti++)
        {
            if (conti == 100)
            {
                i += 100;
                conti = 0;
            }


            Color *p = pixel(img, i, j);
            *p = branco;
        }
    }

    savePng("xadrez.png", img);

    freeImage(img);

    return 0;
}
