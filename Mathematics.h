#ifndef CG2_MATHEMATICS_H
#define CG2_MATHEMATICS_H

typedef struct vec2
{
    float x, y;
} vec2;

float modulo(float x);

float max(float a, float b);

float min(float a, float b);

float areaTri(vec2 a, vec2 b, vec2 c);

void barycentric(vec2 p, vec2 *t, float *b);

vec2 mult(vec2 v, float a);

vec2 soma(vec2 v, vec2 u);

void translateV(vec2 *p, int n, vec2 v, vec2 *r);

vec2 translate(vec2 p, vec2 v);

vec2 multMP2(float M[2][2], vec2 P);

void multMV2(float M[2][2], vec2 *P, int N, vec2 *R);

void multMM2(float M1[2][2], float M2[2][2], float R[2][2], int n);

#endif //CG2_MATHEMATICS_H
