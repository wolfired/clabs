#include <stdbool.h>
#include <stdint.h>

#include "line.h"

void standardize(int32_t* x0, int32_t* y0, int32_t* x1, int32_t* y1, bool* steep, bool* flip_x) {
    *steep = (*x1 > *x0 ? *x1 - *x0 : *x0 - *x1) < (*y1 > *y0 ? *y1 - *y0 : *y0 - *y1);

    if (*steep) {
        *x0 ^= *y0, *y0 ^= *x0, *x0 ^= *y0;
        *x1 ^= *y1, *y1 ^= *x1, *x1 ^= *y1;
    }

    *flip_x = *y0 > *y1;

    if (*flip_x) {
        *x0 = (*x1 << 1) - *x0;
    }

    if (*x0 > *x1) {
        *x0 ^= *x1, *x1 ^= *x0, *x0 ^= *x1;
        *y0 ^= *y1, *y1 ^= *y0, *y0 ^= *y1;
    }
}

void line_dda(int32_t x0, int32_t y0, int32_t x1, int32_t y1, line_stepper stepper, void* voidargs) {
    bool steep = false, flip_x = false;
    standardize(&x0, &y0, &x1, &y1, &steep, &flip_x);

    int32_t x0x0 = x0 << 1;

    float k = (0. + y1 - y0) / (0. + x1 - x0);
    float y = 0. + y0;

    for (int32_t x = x0; x <= x1; ++x) {
        if (steep) {
            stepper(voidargs, (int32_t)(y + .5), flip_x ? x0x0 - x : x);
        } else {
            stepper(voidargs, flip_x ? x0x0 - x : x, (int32_t)(y + .5));
        }
        y += k;
    }
}

/*

F(x, y) = ax + by + c

0 = F(x, y) 直线
0 > F(x, y) 直线上方
0 < F(x, y) 直线下方

坐标系上两点: P0 = (X0, Y0), P1 = (X1, Y1)

dx = X1 - X0
dy = Y1 - Y0

直线一般式: ax + by + c = 0
直线斜截式: y = kx + B
斜率: k
截距: B

k = dy / dx                      =>
y = (dy / dx) * x + B            =>
dx * y = dy * x + B * dx         =>
dy * x - dx * y + B * dx = 0     =>
a = dy, b = -dx, c = B * dx = X1 * Y0 - X0 * Y1

00000000u
000000000
00000000m
000000000
i0000000d

屏幕上有点 Pi, Pu, Pd, 要求经过 Pi 画直线 L
Pm 是 Pu, Pd 数学意义上的中点

Pi: F(Xi, Yi) = 0
Pd: Pd = (Xd, Yd) = (Xi + 1, Yi)
Pu: Pu = (Xu, Yu) = (Xi + 1, Yi + 1)
Pm: Pm = (Xm, Ym) = (Xi + 1, Yi + .5)

di = F(Xi, Yi) = a * Xi + b * Yi + c = 0
dm = F(Xm, Ym) = a * (Xi + 1) + b * (Yi + .5) + c = a * Xi + b * Yi + c + a + .5 * b = di + a + .5 * b = a + .5 * b

当 0 > dm 时, 中点 Pm 在直线 L 上方, 此时点 Pd 更新接近直线 L
dmm = F(Xmm, Ym) = a * (Xi + 2) + b * (Yi + .5) + c = a * Xi + b * Yi + c + 2a + .5 * b = di + 2a + .5 * b = 2a + .5 * b = dm + a

当 0 <= dm 时, 中点 Pm 在直线 L 下方, 此时点 Pu 更新接近直线 L
dmm = F(Xmm, Ymm) = a * (Xi + 2) + b * (Yi + 1.5) + c = a * Xi + b * Yi + c + 2a + 1.5 * b = di + 2a + 1.5 * b = dm + a + b

*/
void line_midpoint(int32_t x0, int32_t y0, int32_t x1, int32_t y1, line_stepper stepper, void* voidargs) {
    bool steep = false, flip_x = false;
    standardize(&x0, &y0, &x1, &y1, &steep, &flip_x);

    int32_t x0x0 = x0 << 1;

    int32_t a = y1 - y0;
    int32_t aa = a << 1;
    int32_t b = x0 - x1;
    int32_t bb = b << 1;

    int32_t dd = aa + b;

    for (int32_t x = x0, y = y0; x <= x1; ++x) {
        if (steep) {
            stepper(voidargs, y, flip_x ? x0x0 - x : x);
        } else {
            stepper(voidargs, flip_x ? x0x0 - x : x, y);
        }
        if (0 > dd) {
            dd += aa;
        } else {
            ++y;
            dd += aa + bb;
        }
    }
}

void line_bresenham(int32_t x0, int32_t y0, int32_t x1, int32_t y1, line_stepper stepper, void* voidargs) {
    bool steep = false, flip_x = false;
    standardize(&x0, &y0, &x1, &y1, &steep, &flip_x);

    int32_t x0x0 = x0 << 1;

    int32_t a = y1 - y0;
    int32_t aa = a << 1;
    int32_t b = x0 - x1;
    int32_t bb = b << 1;

    int32_t ee = b;

    for (int32_t x = x0, y = y0; x <= x1; ++x) {
        if (steep) {
            stepper(voidargs, y, flip_x ? x0x0 - x : x);
        } else {
            stepper(voidargs, flip_x ? x0x0 - x : x, y);
        }
        ee += aa;
        if (0 <= ee) {
            ++y;
            ee += bb;
        }
    }
}