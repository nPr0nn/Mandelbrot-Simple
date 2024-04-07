
#include "../headers/mandlebrot.h"
#include "../headers/image_proc.h"
#include "../headers/cycle_timer.h"

#include <math.h>

int main(){
  int numThreads = 2;
  
  const unsigned int width  = 1600;
  const unsigned int height = 1200;
  const int maxIterations   = 256;

  vec2f p0 = (vec2f){ -2, -1 };
  vec2f p1 = (vec2f){ 1, 1 };
  
  int* output = malloc(sizeof(int)*width*height);
 
  double minThread = 1e30;
  for (int i = 0; i < 5; ++i) {
    memset(output, 0, width * height * sizeof(int));
    double startTime = currentSeconds();
    mandelbrotSerial(p0, p1, width, height, 0, height, maxIterations, output);
    double endTime = currentSeconds();
    minThread = fminf(minThread, endTime - startTime);
  }

  printf("[mandelbrot time]:\t\t[%.3f] ms\n", minThread * 1000);
  write_PNG(output, width, height, "mandelbrot.png", maxIterations);
}
