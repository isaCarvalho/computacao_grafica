#ifndef CG2_COLOR_H
#define CG2_COLOR_H

typedef unsigned char Byte;

typedef struct Color {
    Byte r, g, b;
} Color;

Byte clamp(float v, float a, float b);

Color lerp(float t, Color A, Color B);

Color interpolacaoBilinear(float u, float v, Color A, Color B, Color C, Color D);

Color triLerp (float a1, float a2, float a3, Color c1, Color c2, Color c3);

#endif //CG2_COLOR_H
