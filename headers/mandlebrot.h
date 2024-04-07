#ifndef MANDELBROT_H
#define MANDELBROT_H

typedef struct vec2f{
  float x;
  float y;
} vec2f;
#define square(x) ((x) * (x))

static inline int mandelbrot(float c_re, float c_im, int count);
void mandelbrotSerial(vec2f p0, vec2f p1, int width, int height, int startRow, int endRow, int max_inter, int output[]);

#endif
