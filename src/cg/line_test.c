#include <ctype.h>
#include <errno.h>
#include <float.h>
#include <locale.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stddef.h>

#include "bufio/buf.h"
#include "image/png.h"

#include "line.h"
#include "triangle.h"

typedef struct _PixelImage {
    size_t wid;
    size_t hei;
    size_t size;

    uint8_t* bytes;
} PixelImage_, *PixelImage;

static inline void set_pixel_color(PixelImage img, size_t pixel_x, size_t pixel_y) {
    size_t i = (pixel_y * img->wid * img->size + pixel_x) * 4;
    img->bytes[i + 0] = 0x00;
    img->bytes[i + 1] = 0x00;
    img->bytes[i + 2] = 0x00;
    img->bytes[i + 3] = 0xff;
}

static void set_grid_color(PixelImage img, size_t grid_x, size_t grid_y) {
    grid_y = img->hei - 1 - grid_y;

    size_t offset_x = grid_x * img->size;
    size_t offset_y = grid_y * img->size;

    for (size_t i = 0; i < img->size * img->size; ++i) {
        set_pixel_color(img, offset_x + i % img->size, offset_y + (size_t)(i / img->size));
    }
}

void create(PixelImage* hold, size_t wid, size_t hei, size_t size, bool grid_line) {
    *hold = (PixelImage)malloc(sizeof(PixelImage_));

    size_t pixel_count = sizeof(uint8_t) * wid * hei * size * size * 4;

    (*hold)->bytes = malloc(pixel_count);
    (*hold)->wid = wid;
    (*hold)->hei = hei;
    (*hold)->size = size;

    memset((*hold)->bytes, 0xff, pixel_count);

    if (1 < size && grid_line) {
        for (size_t x = size - 1; x < wid * size; x += size) {
            for (size_t y = 0; y < hei * size; ++y) {
                set_pixel_color(*hold, x, y);
                set_pixel_color(*hold, y, x);
            }
        }
    }
}

void destory(PixelImage* hold) {
    free((*hold)->bytes);
    free(*hold);
    *hold = NULL;
}

void save2png(PixelImage img, const char* filename) {
    Buffer buffer_png = NULL;
    buf_create(&buffer_png, 1024);

    png_encode_pixel_bytes(buffer_png, img->wid * img->size, img->hei * img->size, img->bytes);

    uint8_t* p = buf_take_pointer(buffer_png, 0);

    FILE* file = fopen(filename, "wb");
    fwrite(p, buf_len(buffer_png), 1, file);

    fclose(file);

    buf_delete(&buffer_png);
}

 static inline void pixelimage_point_stepper(void* voidargs, int32_t x, int32_t y) { set_grid_color((PixelImage)voidargs, x, y); }

void line_grid(PixelImage img, int32_t x0, int32_t y0, int32_t x1, int32_t y1) { line_bresenham(x0, y0, x1, y1, pixelimage_point_stepper, img); }

void draw_lines(PixelImage img, const char* filename, line_painter painter) {
    // painter(0, 0, 0, 79, pixelimage_point_stepper, img);
    // painter(0, 79, 79, 79, pixelimage_point_stepper, img);
    // painter(79, 79, 79, 0, pixelimage_point_stepper, img);
    // painter(79, 0, 0, 0, pixelimage_point_stepper, img);

    // painter(3, 5, 17, 47, pixelimage_point_stepper, img);
    // painter(37, 5, 17, 47, pixelimage_point_stepper, img);
    // painter(3, 5, 37, 5, pixelimage_point_stepper, img);

    // painter(57, 5, 93, 16, pixelimage_point_stepper, img);
    // painter(77, 5, 93, 16, pixelimage_point_stepper, img);
    // painter(57, 5, 77, 5, pixelimage_point_stepper, img);

    painter(17, 31, 23, 47, pixelimage_point_stepper, img);
    painter(17, 31, 13, 71, pixelimage_point_stepper, img);
    painter(23, 47, 13, 71, pixelimage_point_stepper, img);

    save2png(img, filename);
}

int main(int argc, char** argv) {
    setlocale(LC_ALL, "C");

    size_t wid = 160;
    size_t hei = 160;
    size_t size = 8;

    PixelImage img_dda = NULL;
    create(&img_dda, wid, hei, size, true);
    draw_lines(img_dda, "E:\\Desktop\\img_dda.png", line_dda);
    destory(&img_dda);

    PixelImage img_midpoint = NULL;
    create(&img_midpoint, wid, hei, size, true);
    draw_lines(img_midpoint, "E:\\Desktop\\img_midpoint.png", line_midpoint);
    destory(&img_midpoint);

    PixelImage img_bresenham = NULL;
    create(&img_bresenham, wid, hei, size, true);
    draw_lines(img_bresenham, "E:\\Desktop\\img_bresenham.png", line_bresenham);
    destory(&img_bresenham);

    triangle_fill(0, 0, 50, 0, 50, 5);

    return EXIT_SUCCESS;
}
