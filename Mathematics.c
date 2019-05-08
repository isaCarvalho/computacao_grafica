#include "Mathematics.h"
#include <stdio.h>

float modulo(float x)
{
    return x < 0 ? x*(-1) : x;
}

float max(float a, float b)
{
    return a > b ? a : b;
}

float min(float a, float b)
{
    return a < b ? a : b;
}

float areaTri(vec2 a, vec2 b, vec2 c)
{
    return (float) ((b.x - a.x)*(b.y + a.y) + (c.x - b.x)*(c.y+b.y) + (a.x - c.x)*(a.y + c.y))/2;
}

void barycentric(vec2 p, vec2 *t, float *b)
{
    float a = areaTri(t[0], t[1], t[2]);

    b[0] = areaTri(p, t[1], t[2]) / a;
    b[1] = areaTri(t[0], p, t[2]) / a;
    b[2] = areaTri(t[0], t[1], p) / a;
}

vec2 mult(vec2 v, float a)
{
    vec2 m = {v.x*a, v.y*a};

    return m;
}

vec2 soma(vec2 v, vec2 u)
{
    vec2 s;
    s.x = v.x + u.x;
    s.y = v.y + u.y;

    return s;
}

vec2 translate(vec2 p, vec2 v)
{
    return soma(p, v);
}

void translateV(vec2 *p, int n, vec2 v, vec2 *r)
{
    for(int i = 0; i < n; i++)
        r[i] = translate(p[i], v);
}

vec2 multMP2(float M[2][2], vec2 P){
    vec2 p = {
            M[0][0]*P.x + M[0][1]*P.y,
            M[1][0]*P.x + M[1][1]*P.y
    };

    return p;
}

void multMV2(float M[2][2], vec2 *P, int N, vec2 *R){
    for(int i = 0; i < N; i++)
        R[i] = multMP2(M, P[i]);
}

void multMM2(float M1[2][2], float M2[2][2], float R[2][2], int n)
{
    float soma;
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++){
            soma=0;
            for(int k=0; k<n; k++) soma += M1[i][k]*M2[k][j];
            R[i][j]=soma;
        }

    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            printf("%f\t", R[i][j]);
        }
        printf("\n");
    }
}