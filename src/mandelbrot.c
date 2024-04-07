
#include "../headers/mandlebrot.h"

static inline int mandelbrot(float c_re, float c_im, int count){
  float z_re = c_re;
  float z_im = c_im;
 
  int i = 0;
  while(i < count){
    if(square(z_re) + square(z_im) > 4.f) break;
    float new_re = square(z_re) - square(z_im);
    float new_im = 2.f * z_re * z_im;
    z_re = c_re + new_re;
    z_im = c_im + new_im;
    i++;
  }
  
  return i;
}

// Serial loop over pixels
void mandelbrotSerial(vec2f p0, vec2f p1, int width, int height, int startRow, int endRow, int max_inter, int output[]){  
  float dx = (p1.x - p0.x) / width;
  float dy = (p1.y - p0.y) / height;
  
  for (int j = startRow; j < endRow; j++) {
    for (int i = 0; i < width; ++i) {
      float x = p0.x + i * dx;
      float y = p0.y + j * dy;
      int index = (j * width + i);
      output[index] = mandelbrot(x, y, max_inter);
    }
  }
}

// Parallel Part
