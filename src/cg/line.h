#ifndef LINE_H
#define LINE_H

typedef void (*point_stepper)(void* voidargs, int32_t x, int32_t y);

typedef void (*line_painter)(int32_t x0, int32_t y0, int32_t x1, int32_t y1, point_stepper stepper, void* voidargs);

void line_dda(int32_t x0, int32_t y0, int32_t x1, int32_t y1, point_stepper stepper, void* voidargs);
void line_midpoint(int32_t x0, int32_t y0, int32_t x1, int32_t y1, point_stepper stepper, void* voidargs);
void line_bresenham(int32_t x0, int32_t y0, int32_t x1, int32_t y1, point_stepper stepper, void* voidargs);

#endif
