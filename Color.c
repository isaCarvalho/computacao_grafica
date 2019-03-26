#include "Color.h"

Byte clamp(float v, float a, float b) {
    if (v < a)
        v = a;
    else if (v > b)
        v = b;

    return (Byte) v;
}

Color lerp(float t, Color A, Color B)
{
    Color C;

    C.r = clamp((1-t)*A.r + t*B.r, 0, 255);
    C.g = clamp((1-t)*A.g + t*B.g, 0, 255);
    C.b = clamp((1-t)*A.b + t*B.b, 0, 255);

    return C;
}
