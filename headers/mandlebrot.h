#ifndef MANDELBROT_H
#define MANDELBROT_H

typedef struct vec2f{
  float x;
  float y;
} vec2f;
#define square(x) ((x) * (x))

void mandelbrotSerial(vec2f p0, vec2f p1, int width, int height, int startRow, int endRow, int maxInterations, int output[]);
void mandelbrotParallel(int numThreads, vec2f p0, vec2f p1, int width, int height, int maxIterations, int output[]);

#endif
