#include "Color.h"

/**
 * Conversão de float para Byte
 * @param v
 * @param a
 * @param b
 * @return
 */
Byte clamp(float v, float a, float b) {
    if (v < a)
        v = a;
    else if (v > b)
        v = b;

    return (Byte) v;
}

/**
 * Funcao que faz a intepolacao linear de uma cor
 * @param t
 * @param A
 * @param B
 * @return
 */
Color lerp(float t, Color A, Color B)
{
    Color C;

    C.r = clamp((1-t)*A.r + t*B.r, 0, 255);
    C.g = clamp((1-t)*A.g + t*B.g, 0, 255);
    C.b = clamp((1-t)*A.b + t*B.b, 0, 255);

    return C;
}

/**
 * Funcao que faz a interpolacão bilinear de uma cor
 * @param u
 * @param v
 * @param A
 * @param B
 * @param C
 * @param D
 * @return
 */
Color interpolacaoBilinear(float u, float v, Color A, Color B, Color C, Color D)
{
    Color AB = lerp(u, A, B);
    Color CD = lerp(u, C, D);

    return lerp(v, AB, CD);
}