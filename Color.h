#ifndef CG2_COLOR_H
#define CG2_COLOR_H

typedef unsigned char Byte;

typedef struct Color {
    Byte r, g, b;
} Color;

Byte clamp(float v, float a, float b);

Color lerp(float t, Color A, Color B);


#endif //CG2_COLOR_H
