#ifndef CG2_MATHEMATICS_H
#define CG2_MATHEMATICS_H

#include <complex>

typedef std::complex<float> complex;

typedef struct vec2
{
    float x, y;
} vec2;

struct vec3{
    float x, y, z;
};

struct vec4{
    float x, y, z, w;
};

struct mat4
{
    float M[4][4];
};

struct Quaternion{
    float a, b, c, d;
};

vec2 operator*(vec2 P, complex a);

vec3 operator+(vec3 u, vec3 v);

vec3 operator*(float a, vec3 v);

vec3 operator-(vec3 u, vec3 v);

vec4 operator+(vec4 u, vec4 v);

vec4 operator*(float a, vec4 v);

vec4 operator*(mat4 A, vec4 u);

mat4 operator*(mat4 A, mat4 B);

Quaternion operator+(Quaternion q1, Quaternion q2);

Quaternion operator*(float alpha, Quaternion q1);

Quaternion operator*(Quaternion q1, Quaternion q2);

vec2 toVec2(complex c);

vec2 mult(vec2 v, float a);

vec2 soma(vec2 v, vec2 u);

vec2 translate(vec2 p, vec2 v);

vec2 multMP2(float M[2][2], vec2 P);

vec2 bezier_cubica(vec2 *p, float t);

vec2 decasteljau(vec2 *P, float t);

vec3 vec4to3(vec4 u);

vec3 normalizado(vec3 u);

vec3 cross(vec3 u, vec3 v);

vec4 cyl_to_cart(float z, float t, float ang);

vec4 waves (float u, float v);

vec4 sphere (float u, float v);

vec4 fun (float u, float v);

mat4 multMM4(mat4 M1, mat4 M2);

mat4 translate(float a, float b, float c);

mat4 scale(float a, float b, float c);

mat4 rotate_x(float a);

mat4 rotate_y(float a);

mat4 rotate_z(float a);

mat4 orthogonal(float l, float r, float t, float b, float n, float f);

mat4 frustum(float l, float r, float b, float t, float n, float f);

mat4 lookAt(vec3 O, vec3 C, vec3 Up);

mat4 perspective(float ang, float a, float n, float f);

complex toComplex(vec2 P);

float dot(vec3 u, vec3 v);

float norma(vec3 u);

float modulo(float x);

float max(float a, float b);

float min(float a, float b);

float areaTri(vec2 a, vec2 b, vec2 c);

void barycentric(vec2 p, vec2 *t, float *b);

void translateV(vec2 *p, int n, vec2 v, vec2 *r);

void multMV2(float M[2][2], vec2 *P, int N, vec2 *R);

void multMM2(float M1[2][2], float M2[2][2], float R[2][2], int n);

void multMV4(mat4 M, vec4 *P, int N, vec4 *R);

void limitesVetor (vec2 *pts, int tam, int *xmin, int *ymin, int *xmax, int *ymax);

int circle(int x, int y);

int line(int x, int y);

#endif //CG2_MATHEMATICS_H
