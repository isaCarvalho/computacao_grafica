#include "Mathematics.h"
#include <stdio.h>

vec2 operator*(vec2 P, complex a){
    complex p = toComplex(P);
    return toVec2(p*a);
}

vec3 operator+(vec3 u, vec3 v)
{
    return {u.x + v.x, u.y + v.y, u.z + v.z};
}

vec3 operator*(float a, vec3 v)
{
    return {a*v.x, a*v.y, a*v.z};
}

vec3 operator-(vec3 u, vec3 v)
{
    return {u.x - v.x, u.y - v.y, u.z - v.z};
}

vec4 operator*(mat4 A, vec4 u)
{
    return {
            A.M[0][0]*u.x + A.M[0][1]*u.y + A.M[0][2]*u.z + A.M[0][3]*u.w,
            A.M[1][0]*u.x + A.M[1][1]*u.y + A.M[1][2]*u.z + A.M[1][3]*u.w,
            A.M[2][0]*u.x + A.M[2][1]*u.y + A.M[2][2]*u.z + A.M[2][3]*u.w,
            A.M[3][0]*u.x + A.M[3][1]*u.y + A.M[3][2]*u.z + A.M[3][3]*u.w
    };
}

vec4 operator+(vec4 u, vec4 v){
    return {u.x + v.x, u.y + v.y, u.z + v.z, u.w + v.w};
}

vec4 operator*(float a, vec4 v){
    return {a*v.x, a*v.y, a*v.z, a*v.w};
}

mat4 operator*(mat4 A, mat4 B)
{
    return multMM4(A, B);
}

Quaternion operator+(Quaternion q1, Quaternion q2){
    Quaternion q;
    q.a = q1.a + q2.a;
    q.b = q1.b + q2.b;
    q.c = q1.c + q2.c;
    q.d = q1.d + q2.d;
    return q;
}

Quaternion operator*(float alpha, Quaternion q1){
    Quaternion q;
    q.a = alpha*q1.a;
    q.b = alpha*q1.b;
    q.c = alpha*q1.c;
    q.d = alpha*q1.d;
    return q;
}

Quaternion operator*(Quaternion q1, Quaternion q2){
    Quaternion q;

    q.a = (q1.a * q2.a) - (q1.b * q2.b) - (q1.c * q2.c) - (q1.d * q2.d);
    q.b = (q1.a * q2.b) + (q1.b * q2.a) + (q1.c * q2.d) - (q1.d * q2.c);
    q.c = (q1.a * q2.c) - (q1.b * q2.d) + (q1.c * q2.a) - (q1.d * q2.b);
    q.d = (q1.a * q2.d) + (q1.b * q2.c) - (q1.c * q2.b) + (q1.d * q2.a);

    return q;
}

vec2 toVec2(complex c){
    return {c.real(), c.imag()};
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

vec2 multMP2(float M[2][2], vec2 P){
    vec2 p = {
            M[0][0]*P.x + M[0][1]*P.y,
            M[1][0]*P.x + M[1][1]*P.y
    };

    return p;
}

vec2 translate(vec2 p, vec2 v)
{
    return soma(p, v);
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

vec3 normalizado(vec3 u)
{
    float n = norma(u);

    return {(u.x / n), (u.y / n), (u.z / n)};
}

vec3 cross(vec3 u, vec3 v)
{
    return {(u.y*v.z - v.y*u.z), (v.x*u.z - u.x*v.z), (u.x*v.y - v.x*u.y)};
}

vec3 vec4to3(vec4 u){
    return {u.x/u.w, u.y/u.w, u.z/u.w};
}

vec4 cyl_to_cart(float z, float t, float ang)
{
    return {t*sin((double) ang), t*cos((double) ang), z, 1};
}

vec4 waves (float u, float v)
{
    return {u, v, sin(u*v/4), 1};
}

vec4 sphere (float u, float v)
{
    return {cos(u)*sin(v), sin(u)*sin(v), cos(v), 1};
}

vec4 fun (float u, float v)
{
    return {2*sin(u), 3*cos(u), v, 1};
}

mat4 multMM4(mat4 M1, mat4 M2)
{
    float soma;

    mat4 R;

    for(int i=0; i<4; i++)
        for(int j=0; j<4; j++){
            soma=0;
            for(int k=0; k<4; k++) soma += M1.M[i][k]*M2.M[k][j];
            R.M[i][j]=soma;
        }

    return R;
}

mat4 translate(float a, float b, float c)
{
    return {
            {
                    { 1, 0, 0, a },
                    { 0, 1, 0, b },
                    { 0, 0, 1, c },
                    { 0, 0, 0, 1 }
            }
    };
}

mat4 scale(float a, float b, float c)
{
    return {
            {
                    { a, 0, 0, 0 },
                    { 0, b, 0, 0 },
                    { 0, 0, c, 0 },
                    { 0, 0, 0, 1 }
            }
    };
}

mat4 rotate_x(float a)
{
    return {
            {
                    { 1, 0, 0, 0 },
                    { 0, cos(a), -sin(a), 0 },
                    { 0, sin(a), cos(a), 0 },
                    { 0, 0, 0, 1 }
            }
    };
}

mat4 rotate_y(float a)
{
    return {
            {
                    { cos(a), 0, sin(a), 0 },
                    { 0, 1, 0, 0 },
                    { -sin(a), 0, cos(a), 0 },
                    { 0, 0, 0, 1 }
            }
    };
}

mat4 rotate_z(float a)
{
    return {
            {
                    { cos(a), -sin(a), 0, 0 },
                    { sin(a), cos(a), 0, 0 },
                    { 0, 0, 1, 0 },
                    { 0, 0, 0, 1 }
            }
    };
}

mat4 orthogonal(float l, float r, float t, float b, float n, float f)
{
    return {
            {
                    {2/(r-l), 0, 0, -(r+l)/(r-l)},
                    {0, 2/(t-b), 0, -(t+b)/(t-b)},
                    {0, 0, 2/(n-f), -(n+f)/(n-f)},
                    {0, 0, 0, 1}
            }
    };
}

mat4 frustum(float l, float r, float b, float t, float n, float f)
{
    return {
            {
                    {(float)-(2*n)/(r-l), 0, (r+l)/(r-l), 0},
                    {0,(float) -(2*n)/(t-b), (t+b)/(t-b), 0},
                    {0, 0, (f+b)/(f-n), (float)(2*n*f)/(n-f)},
                    {0, 0, -1, 0}
            }
    };
}

mat4 lookAt(vec3 O, vec3 C, vec3 Up)
{
    vec3 upN = normalizado(Up);

    vec3 f = normalizado(C-O);

    vec3 s = normalizado(cross(f, upN));

    vec3 u = cross(s, f);

    mat4 m1 =  {
            s.x, s.y, s.z, 0,
            u.x, u.y, u.z, 0,
            -f.x, -f.y, -f.z, 0,
            0, 0, 0, 1
    };

    mat4 m2 =
            {
                    1, 0, 0, O.x,
                    0, 1, 0, O.y,
                    0, 0, 1, O.z,
                    0, 0, 0, 1
            };

    return multMM4(m1, m2);
}

mat4 perspective(float ang, float a, float n, float f)
{
    if (n < 0)
        n = n*(-1);

    float t = n * tan(ang/2);
    float b = -t;
    float r = t*a;
    float l = -r;

    return frustum(l, r, b, t, n, f);
}

complex toComplex(vec2 P){
    return {P.x, P.y};
}

float dot(vec3 u, vec3 v)
{
    return u.x * v.x + u.y * v.y + u.z * v.z;
}

float norma(vec3 u)
{
    return sqrt(u.x*u.x + u.y*u.y + u.z*u.z);
}

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

void translateV(vec2 *p, int n, vec2 v, vec2 *r)
{
    for(int i = 0; i < n; i++)
        r[i] = translate(p[i], v);
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
}

void multMV4(mat4 M, vec4 *P, int N, vec4 *R){
    for(int i = 0; i < N; i++)
        R[i] = M * P[i];
}

void limitesVetor (vec2 *pts, int tam, int *xmin, int *ymin, int *xmax, int *ymax)
{
    int i;

    *xmin = pts[0].x;
    *ymin = pts[0].y;
    *xmax = pts[0].x;
    *ymax = pts[0].y;

    for(i=1; i<tam; i++){
        if (pts[i].x < *xmin)
            *xmin = pts[i].x;
        if (pts[i].y < *ymin)
            *ymin = pts[i].y;
        if (pts[i].x > *xmax)
            *xmax = pts[i].x;
        if (pts[i].y > *ymax)
            *ymax = pts[i].y;
    }
}

int circle(int x, int y)
{
    int r = 200;

    return (x-200)*(x-200) + (y-200)*(y-200) - r*r;
}

int line(int x, int y)
{
    int a = 2, b = 3;

    return a*x + b - y;
}