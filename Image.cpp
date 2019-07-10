#include "Image.h"
#include "Color.h"
#include "math.h"
#include <stdbool.h>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION

#include "stb_image_write.h"
#include "stb_image.h"

Image newImage(int w, int h, bool useZBuffer)
{
    Image img = {w, h, (Color*) malloc(w*h*sizeof(Color))};

    img.ZBuffer = NULL;
    if(useZBuffer)
        img.ZBuffer = (float*)malloc(w*h*sizeof(float));

    initZBuffer(img);

    return img;
}

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

Image combinacaoImg(Image A, Image B, float t)
{
    Image img = newImage(A.h, B.h);

    for (int i = 0; i < A.h; i++)
    {
        for (int j = 0; j < A.w; j++)
        {
            vec2 p = {(float) i, (float)j};
            draw_pixel(img, lerp(t, *pixel(A, i, j), *pixel(B, i, j)), p);
        }
    }

    return img;
}

Image xadrez(Image img)
{
    Color preto = {0, 0, 0};
    Color branco = {255, 255, 255};

    initImage(img, preto);

    for(int j = 0; j < img.h; j += 200)
        for(int i = 0; i < img.w; i += 200)
            draw_rectangle(img, branco, i, j, i + 100, j + 100);

    for(int j = 100; j < img.h; j += 200)
        for(int i = 100; i < img.w; i += 200)
            draw_rectangle(img, branco, i, j, i + 100, j + 100);

    return img;
}

Image imagemBonitinha(Image img)
{
    Color A = {255, 0, 0}, B = {0, 255, 0}, C = {0, 0, 255}, D = {255, 0, 255};

    for (int j = 0; j < img.h; j++)
    {
        float v = (float) j/(img.h-1);

        for (int i = 0; i < img.w; i++)
        {
            float u = (float) i/(img.w-1);
            vec2 p = {(float)i, (float)j};
            draw_pixel(img, interpolacaoBilinear(u, v, A, B, C, D), p);
        }
    }

    return img;
}

Color *pixel(Image img, float x, float y)
{
    return img.data + (int)(img.w*y+x);
}

float* zbuffer(Image img, int x, int y){
    return img.ZBuffer + (y*img.w + x);
}

vec3 toScreen(Image img, vec4 P){
    vec3 v = vec4to3(P);
    v.x = ((v.x+1)*img.w - 1)/2;
    v.y = ((v.y+1)*img.h - 1)/2;
    return v;
}

void freeImage(Image img)
{
    free(img.data);
    free(img.ZBuffer);
}

void initZBuffer(Image img){
    if(img.ZBuffer == NULL)
        return;

    for(int y = 0; y < img.h; y++)
        for(int x = 0; x < img.w; x++){
            float* zb = zbuffer(img, x, y);
            *zb = -1;
        }
}

void initImage(Image img, Color color)
{
    draw_rectangle(img, color, 0, 0, img.w, img.h);
}

void savePng(const char *filename, Image img)
{
    stbi_flip_vertically_on_write(1);
    stbi_write_png(filename, img.w, img.h, 3, img.data, 0);
}

void draw_pixel(Image img, Color color, vec2 p)
{
    if (p.x >= 0 && p.x < img.w && p.y >= 0 && p.y < img.h)
    {
        Color *px = pixel(img, (int) p.x, (int) p.y);
        *px = color;
    }
}

void draw_rectangle(Image img, Color color, int x1, int y1, int x2, int y2)
{
    for (int i = x1; i < x2; i++)
        for (int j = y1; j < y2; j++)
        {
            vec2 p = {(float)i, (float)j};
            draw_pixel(img, color, p);
        }
}

void draw_function(Image img, Color color, int funcao(int, int))
{
    for (int i = 0; i < img.w; i++)
        for (int j = 0; j < img.h; j++)
            if (funcao(i, j) <= 0)
            {
                vec2 p = {(float)i, (float)j};
                draw_pixel(img, color, p);
            }
}

unsigned char code(float x, float y, float xmin, float xmax, float ymin, float ymax)
{
    unsigned char code=0;

    if (y > ymax)
        code += 8;

    else if (y < ymin)
        code += 4;

    else if (x > xmax)
        code += 2;

    else if (x < xmin)
        code += 1;

    return code;
}

void draw_line(Image img, Color color, vec2 p0, vec2 p1, float z0, float z1)
{

    unsigned char outcode0, outcode1, outcodeOut;

    double x, y; bool accept = false, done = false;

    outcode0 = code(p0.x, p0.y, 0, img.w, 0, img.h);
    outcode1 = code(p1.x, p1.y, 0, img.w, 0, img.h);

    do {
        if (outcode0 == 0 && outcode1 == 0)
        {
            accept = true;
            done = true;
        }
        else if((outcode0 & outcode1) != 0)
        {
            done = true;
        }
        else{
            outcodeOut = (outcode0 != 0) ? outcode0 : outcode1;
            if (outcodeOut & 8)
            {
                x = p0.x + (p1.x - p0.x) * (img.h - p0.y) / (p1.y - p0.y);
                y = img.h;
            }
            else if(outcodeOut & 4)
            {
                x = p0.x + (p1.x - p0.x) * (0 - p0.y) / (p1.y - p0.y);
                y = 0;
            }
            else if(outcodeOut & 2)
            {
                y = p0.y + (p1.y - p0.y) * (img.w - p0.x) / (p1.x - p0.x);
                x = img.w;
            }
            else if(outcodeOut & 1)
            {
                y = p0.y + (p1.y - p0.y) * (0 - p0.x) / (p1.x - p0.x);
                x = 0;
            }

            if (outcodeOut == outcode0)
            {
                p0.x = x;
                p0.y = y;
                outcode0 = code(p0.x, p0.y, 0, img.w, 0, img.h);
            }
            else{
                p1.x = x;
                p1.y = y;
                outcode1 = code(p1.x, p1.y, 0, img.w, 0, img.h);
            }
        }
    } while (!done);

    if (accept)
        draw_line_aux(img, color, p0, p1, z0, z1);
}

void verificaZBuffer (Image img, Color color, vec2 p, float z)
{
    if (img.useZBuffer)
    {
        float* zb = zbuffer(img, p.x, p.y);

        if(z != 0 && z > *zb)
        {
            draw_pixel(img, color, p);
            *zb = z;
        }
    }
    else
    {
        draw_pixel(img, color, p);
    }
}

void draw_line_aux(Image img, Color color, vec2 p0, vec2 p1, float z0, float z1)
{

    float m = (float) modulo(p1.y - p0.y) / modulo(p1.x - p0.x);
    int dx = (int) modulo(p1.x - p0.x);
    int dy = (int) modulo(p1.y - p0.y);

    float z = z0;

    // Reta horizontal
    if (p0.y == p1.y)
    {
        if (p0.x > p1.x)
        {
            vec2 aux = p0;
            p0 = p1;
            p1 = aux;
            z = z1;
        }

        for (int i = (int) p0.x; i <= p1.x; i++)
        {
            vec2 p = {(float)i, p0.y};
            verificaZBuffer(img, color, p, z);
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
            z = z1;
        }

        for (int i = (int) p0.y; i <= p1.y; i++)
        {
            vec2 p = {p0.x, (float)i};
            verificaZBuffer(img, color, p, z);
        }
    }

    // Reta y = +-x;
    else if (modulo(p1.x - p0.x) == modulo(p1.y - p0.y))
    {
        for (int i = (int) p0.x, j = (int) p0.y; i <= p1.x; i++)
        {
            vec2 p = {(float) i, (float)j};
            verificaZBuffer(img, color, p, z);

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
            vec2 p = {(float)i, (float)y};
            verificaZBuffer(img, color, p, z);

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
            vec2 p = {(float)x, (float)i};
            verificaZBuffer(img, color, p, z);

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

void draw_line(Image img, Color color, vec3 p0, vec3 p1)
{
    draw_line(img, color, (vec2) {p0.x, p0.y}, (vec2) {p1.x, p1.y}, p0.z, p1.z);
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
                        {(float)xc+x, (float)yc+y},
                        {(float)yc+y, (float)xc+x},
                        {(float)xc+x, (float)yc-y},
                        {(float)yc-y, (float)xc+x},
                        {(float)xc-x, (float)yc+y},
                        {(float)yc+y, (float)xc-x},
                        {(float)xc-x, (float)yc-y},
                        {(float)yc-y, (float)xc-x}
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
    int x0 = (int) floor(min(p[0].x, min(p[1].x, p[2].x)));
    int x1 = (int) ceil(max(p[0].x, max(p[1].x, p[2].x)));

    int y0 = (int) floor(min(p[0].y, min(p[1].y, p[2].y)));
    int y1 = (int) ceil(max(p[0].y, max(p[1].y, p[2].y)));

    float b[3];

    for (int i = x0; i < x1; i++)
    {
        for (int j = y0; j < y1; j++)
        {
            vec2 _p = {(float)i, (float)j};
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

void draw_triangle(Image img, Color *c, vec3 *p)
{
    vec2 vet[3];

    for (int i=0; i<3; i++)
        vet[i] = {p[i].x, p[i].y};

    draw_triangle(img, c, vet);
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

void draw_line(Image img, Color color, vec4 A, vec4 B)
{
    vec3 v0 = toScreen(img, A);
    vec3 v1 = toScreen(img, B);

    draw_line(img, color, v0, v1);
}

void draw_lines(Image img, Color color, vec4 *p, int n)
{
    for (int i = 0; i < n-1; i += 2)
    {
        draw_line(img, color, p[i], p[i+1]);
    }
}

void draw_line_strip(Image img, Color color, vec4 *p, int n)
{
    for (int i = 0; i < n-1; i++)
    {
        draw_line(img, color, p[i], p[i+1]);
    }
}

void draw_line_loop(Image img, Color color, vec4 *p, int n)
{
    draw_line_strip(img, color, p, n);
    draw_line(img, color, p[n-1], p[0]);
}

void draw_elements_lines(Image img, Color color, vec4 *p, const int *indices, int n)
{
    for (int i = 0; i < n-1; i+=2)
    {
        draw_line(img, color, p[indices[i]], p[indices[i+1]]);
    }
}

void draw_elements_line_strip(Image img, Color color, vec4 *p, const int *indices, int n)
{
    for (int i = 0; i < (n-1); i++)
        draw_line(img, color, p[indices[i]], p[indices[i+1]]);
}

void draw_elements_line_loop(Image img, Color color, vec4 *p, const int *indices, int n)
{
    draw_elements_line_strip(img, color, p, indices, n);
    draw_line(img, color, p[indices[n-1]], p[indices[0]]);
}

void draw_triangle(Image img, Color C[3], vec4 P[3]){
    vec3 P3[] = {
            toScreen(img, P[0]),
            toScreen(img, P[1]),
            toScreen(img, P[2])
    };
    draw_triangle(img, C, P3);
}

void draw_triangles(Image img, Color *color, vec4 *p, int n)
{
    for (int i = 0; i < n; i += 3)
        draw_triangle(img, color+i, p+i);
}

void draw_triangle_strip(Image img, Color *color, vec4 *p, int n)
{
    for (int i = 0; i < n; i++)
        draw_triangle(img, color+i, p+i);
}

void draw_triangle_fan(Image img, Color *c, vec4 *p, int n)
{
    vec4 _p[3] = {p[0]};
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

void draw_elements_triangles(Image img, Color *c, vec4 *p, const int *indices, int n)
{
    vec4 _p[3];
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

void draw_wireframe(Image img, Color color, mat4 M, int m, int n, float u0, float u1, float v0, float v1)
{
    int N = m*n;

    float du = (u1-u0)/(m-1), dv = (v1-v0)/(n-1);

    vec4 *P = (vec4*) malloc(N*sizeof(vec4));

    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            float u = u0 + i*du;
            float v = v0 + j*dv;

            int ij = i + j*m;
            P[ij] = {u, v, sin(u*v/4), 1};
        }
    }

    int Ni = 2*(3*N - 2*m - 2*n + 1);
    int *indices = (int*) malloc(Ni*sizeof(int));

    int k = 0;
    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            int ij = i + j*m;
            if(i < m-1){
                indices[k++] = ij;
                indices[k++] = ij+1;
            }

            if(j < n-1){
                indices[k++] = ij;
                indices[k++] = ij+m;
            }

            if(i < m-1 && j < n-1){
                indices[k++] = ij+1;
                indices[k++] = ij+m;
            }
        }
    }

    vec4 *MP2 = (vec4*) malloc(N*sizeof(vec4));

    multMV4(M, P, N, MP2);

    draw_elements_lines(img, color, MP2, indices, Ni);
}

void draw_model(Image img, Color *color, mat4 M, vec4 (*f)(float, float), int m, int n, float u0, float u1, float v0, float v1)
{
    int N = m*n;

    float du = (u1-u0)/(m-1), dv = (v1-v0)/(n-1);

    vec4 P[N];
    Color C[N];

    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            float u = u0 + i*du;
            float v = v0 + j*dv;

            int ij = i + j*m;
            P[ij] = f(u, v);
            C[ij] = interpolacaoBilinear((float)i/m,(float)j/n, color[0], color[1], color[2], color[3]);
        }
    }

    int Ni = 2*(3*N - 2*m - 2*n + 1);
    int *indices = (int*) malloc(Ni*sizeof(int));

    int k = 0;
    for(int i = 0; i < m-1; i++)
    {
        for(int j = 0; j < n-1; j++)
        {
            int ij = i + j*m;
            indices[k++] = ij;
            indices[k++] = ij+1;
            indices[k++] = ij+m;

            indices[k++] = ij+m+1;
            indices[k++] = ij+m;
            indices[k++] = ij+1;

        }
    }
    vec4 MP2[N];

    multMV4(M, P, N, MP2);

    draw_elements_triangles(img, C, MP2, indices, k);
}