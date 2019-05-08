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
Image newImage(int w, int h)
{
    Image img = {w, h, (Color*) malloc(w*h*sizeof(Color))};
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

    Image img = newImage(width, height);

    for (int i = 0, j = 0; i < (img.w*img.h); i++, j+=nrChannels)
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
    draw_rectangle(img, color, 0, 0, img.w, img.h);
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

/**
 * Função que retorna um ponteiro para a cor de um pixel da imagem
 * @param img
 * @param x
 * @param y
 * @return
 */
Color *pixel(Image img, float x, float y)
{
    return img.data + (int)(img.w*y+x);
}

/**
 * Função que pinta um pixel da imagem
 * @param img
 * @param color
 * @param x
 * @paragm y
 */
void draw_pixel(Image img, Color color, vec2 p)
{
    Color *px = pixel(img, p.x, p.y);
    *px = color;
}

/**
 * Função que aplica o filtro luminancia a uma imagem
 * @param img
 * @return
 */
Image luminancia(Image img)
{
    Image imgl = newImage(img.w, img.h);

    for (int i = 0; i < img.w*img.h; i++)
    {
        float r = 0.176*img.data[i].r;
        float g = 0.810*img.data[i].g;
        float b = 0.011*img.data[i].b;

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
            vec2 p = {i, j};
            draw_pixel(img, lerp(t, *pixel(A, i, j), *pixel(B, i, j)), p);
        }
    }

    return img;
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
void draw_rectangle(Image img, Color color, int x1, int y1, int x2, int y2)
{
    for (int i = x1; i < x2; i++)
        for (int j = y1; j < y2; j++)
        {
            vec2 p = {i, j};
            draw_pixel(img, color, p);
        }
}

void draw_function(Image img, Color color, int funcao(int, int))
{
    for (int i = 0; i < img.w; i++)
        for (int j = 0; j < img.h; j++)
            if (funcao(i, j) <= 0)
            {
                vec2 p = {i, j};
                draw_pixel(img, color, p);
            }
}

void draw_line(Image img, Color color, vec2 p0, vec2 p1)
{
    float m = (float) modulo(p1.y - p0.y) / modulo(p1.x - p0.x);
    int dx = (int) modulo(p1.x - p0.x);
    int dy = (int) modulo(p1.y - p0.y);

    // Reta horizontal
    if (p0.y == p1.y)
    {
        if (p0.x > p1.x)
        {
            vec2 aux = p0;
            p0 = p1;
            p1 = aux;
        }

        for (int i = (int) p0.x; i <= p1.x; i++)
        {
            vec2 p = {i, p0.y};
            draw_pixel(img, color, p);
        }
    }

    // Reta vertical
    else if (p0.x == p1.x)
    {
        if (p0.y > p1.y)
        {
            vec2 aux = p0;
            p0 = p1;
            p1 = aux;
        }

        for (int i = (int) p0.y; i <= p1.y; i++)
        {
            vec2 p = {p0.x, i};
            draw_pixel(img, color, p);
        }
    }

    // Reta y = +-x;
    else if (modulo(p1.x - p0.x) == modulo(p1.y - p0.y))
    {
        for (int i = (int) p0.x, j = (int) p0.y; i <= p1.x; i++)
        {
            vec2 p = {i, j};
            draw_pixel(img, color, p);

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
            vec2 aux = p0;
            p0 = p1;
            p1 = aux;
        }

        int D = 2*dy - dx;

        int y = (int) p0.y;

        for (int i = (int) p0.x; i <= p1.x; i++)
        {
            vec2 p = {i, y};
            draw_pixel(img, color, p);

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
            vec2 aux = p0;
            p0 = p1;
            p1 = aux;
        }

        int D = 2*dx - dy;

        int x = (int) p0.x;

        for (int i = (int) p0.y; i <= p1.y; i++)
        {
            vec2 p = {x, i};
            draw_pixel(img, color, p);

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

void draw_lines(Image img, Color color, vec2 *p, int n)
{
    for (int i = 0; i < n-1; i += 2)
    {
        draw_line(img, color, p[i], p[i+1]);
    }
}

void draw_line_strip(Image img, Color color, vec2 *p, int n)
{
    for (int i = 0; i < n-1; i++)
    {
        draw_line(img, color, p[i], p[i+1]);
    }
}

void draw_line_loop(Image img, Color color, vec2 *p, int n)
{
    draw_line_strip(img, color, p, n);
    draw_line(img, color, p[n-1], p[0]);
}

void draw_elements_lines(Image img, Color color, vec2 *p, const int *indices, int n)
{
    for (int i = 0; i < (n-1); i+=2)
        draw_line(img, color, p[indices[i]], p[indices[i+1]]);
}

void draw_elements_line_strip(Image img, Color color, vec2 *p, const int *indices, int n)
{
    for (int i = 0; i < (n-1); i++)
        draw_line(img, color, p[indices[i]], p[indices[i+1]]);
}

void draw_elements_line_loop(Image img, Color color, vec2 *p, const int *indices, int n)
{
    draw_elements_line_strip(img, color, p, indices, n);
    draw_line(img, color, p[indices[n-1]], p[indices[0]]);
}

void draw_circle(Image img, Color color, int xc, int yc, int R)
{
    int y = R;
    int d = 1-R;

    for (int x = 0; x <= y; x++)
    {
        vec2 oc[8] =
                {
                        {xc+x, yc+y},
                        {yc+y, xc+x},
                        {xc+x, yc-y},
                        {yc-y, xc+x},
                        {xc-x, yc+y},
                        {yc+y, xc-x},
                        {xc-x, yc-y},
                        {yc-y, xc-x}
                };

        for (int j = 0; j < 8; j++)
        {
            draw_pixel(img, color, oc[j]);
        }

        if (d > 0)
        {
            d += 2*x - 2*y + 5;
            y--;
        }
        else
        {
            d += 2 * x + 3;
        }
    }
}

void draw_triangle(Image img, Color *c, vec2 *p)
{
    int x0 = (int) min(p[0].x, min(p[1].x, p[2].x));
    int x1 = (int) max(p[0].x, max(p[1].x, p[2].x));

    int y0 = (int) min(p[0].y, min(p[1].y, p[2].y));
    int y1 = (int) max(p[0].y, max(p[1].y, p[2].y));

    float b[3];

    for (int i = x0; i < x1; i++)
    {
        for (int j = y0; j < y1; j++)
        {
            vec2 _p = {i, j};
            barycentric(_p, p, b);

            if (b[0] >= 0 && b[0] <= 1 && b[1] >= 0 && b[1] <= 1 && b[2] >= 0 && b[2] <= 1)
            {
                Color _c;
                _c.r = clamp(b[0]*c[0].r + b[1]*c[1].r + b[2]*c[2].r, 0, 255);
                _c.g = clamp(b[0]*c[0].g + b[1]*c[1].g + b[2]*c[2].g, 0, 255);
                _c.b = clamp(b[0]*c[0].b + b[1]*c[1].b + b[2]*c[2].b, 0, 255);

                draw_pixel(img, _c, _p);
            }
        }
    }
}

void draw_triangles(Image img, Color *color, vec2 *p, int n)
{
    for (int i = 0; i < n; i += 3)
        draw_triangle(img, color+i, p+i);
}

void draw_triangle_strip(Image img, Color *color, vec2 *p, int n)
{
    for (int i = 0; i < n; i++)
        draw_triangle(img, color+i, p+i);
}

void draw_triangle_fan(Image img, Color *c, vec2 *p, int n)
{
    vec2 _p[3] = {p[0]};
    Color _c[3] = {c[0]};

    for (int i = 1; i < n-1; i++)
    {
        _p[1] = p[i];
        _p[2] = p[i+1];

        _c[1] = c[i];
        _c[2] = c[i+1];

        draw_triangle(img, _c, _p);
    }
}

void draw_elements_triangles(Image img, Color *c, vec2 *p, const int *indices, int n)
{
    vec2 _p[3];
    Color _c[3];

    for (int i = 0; i < n-2; i += 3)
    {
        _p[0] = p[indices[i]];
        _p[1] = p[indices[i+1]];
        _p[2] = p[indices[i+2]];

        _c[0] = c[indices[i]];
        _c[1] = c[indices[i+1]];
        _c[2] = c[indices[i+2]];

        draw_triangle(img, _c, _p);
    }
}

vec2 decasteljau(vec2 *P, float t)
{
    vec2 Q[3] = {
            soma(mult(P[0], (1-t)), mult(P[1], t)),
            soma(mult(P[1], (1-t)), mult(P[2], t)),
            soma(mult(P[2], (1-t)), mult(P[3], t))
    };

    vec2 R[2] = {
            soma(mult(Q[0], (1-t)), mult(Q[1], t)),
            soma(mult(Q[1], (1-t)), mult(Q[2], t))
    };

    return soma(mult(R[0], (1-t)), mult(R[1], t));
}

vec2 bezier_cubica(vec2 *p, float t)
{
    float a0 = (1-t)*(1-t)*(1-t);
    float a1 = 3*t*(1-t)*(1-t);
    float a2 = 3*t*t*(1-t);
    float a3 = t*t*t;

    vec2 c = mult(p[0], a0);
    c = soma(c, mult(p[1], a1));
    c = soma(c, mult(p[2], a2));
    c = soma(c, mult(p[3], a3));

    return c;
}

void draw_bezier_splines(Image img, Color c, vec2 *p, int n)
{
    for (int j = 0; j < n-1; j+=3)
    {
        int N = 50;
        vec2 C[N];
        for(int i = 0; i < N; i++){
            float t = i/(N-1.0);
            C[i] = bezier_cubica(p+j, t);
        }
        draw_line_strip(img, c, C, N);
    }
}