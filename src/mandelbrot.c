
#include "../headers/mandlebrot.h"

#include <stdio.h>
#include <stdlib.h>

//--------------------------------------------------------------------------
// Serial Implementation
//--------------------------------------------------------------------------

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
void mandelbrotSerial(vec2f p0, vec2f p1, int width, int height, int startRow, int endRow, int maxInterations, int output[]){  
  float dx = (p1.x - p0.x) / width;
  float dy = (p1.y - p0.y) / height;
  
  for (int j = startRow; j < endRow; j++) {
    for (int i = 0; i < width; ++i) {
      float x = p0.x + i * dx;
      float y = p0.y + j * dy;
      int index = (j * width + i);
      output[index] = mandelbrot(x, y, maxInterations);
    }
  }
}

//--------------------------------------------------------------------------
// Parallel Implementation
//--------------------------------------------------------------------------

#include <pthread.h>

typedef struct {
  vec2f p0;
  vec2f p1;
  unsigned int width;
  unsigned int height;
  int maxIterations;
  int* output;
  int threadId;
  int numThreads;
} worker_args;


void* worker_thread_start(void *arg) {
  worker_args *args = (worker_args*) arg;
  int totalRows = (int) args->height / args->numThreads;
  int startRow  = args->threadId * totalRows;

  if (args->threadId == args->numThreads - 1){
    totalRows = args->height - startRow;
  }

  int endRow = startRow + totalRows;  
  vec2f p0 = { args->p0.x, args->p0.y };
  vec2f p1 = { args->p1.x, args->p1.y };

  mandelbrotSerial(p0, p1, args->width, args->height, startRow, endRow, args->maxIterations, args->output);
  return NULL;
}

// Multi-threaded implementation of mandelbrot set image generation.
// Threads of execution are created by spawning pthreads.
void mandelbrotParallel(int numThreads, vec2f p0, vec2f p1, int width, int height, int maxIterations, int output[]) {
  static const int MAX_THREADS = 64;

  if(numThreads > MAX_THREADS){
    fprintf(stderr, "Error: Max allowed threads is %d\n", MAX_THREADS);
    exit(1);
  }

  pthread_t workers[MAX_THREADS];
  worker_args args[MAX_THREADS];

  for (int i = 0; i < numThreads; i++) {
    args[i].p0 = p0;
    args[i].p1 = p1;
    args[i].width = width;
    args[i].height = height;
    args[i].maxIterations = maxIterations;
    args[i].numThreads = numThreads;
    args[i].output = output;
    args[i].threadId = i;

    int ret = pthread_create(&workers[i], NULL, worker_thread_start, (void *)&args[i]);
    if (ret != 0) {
      fprintf(stderr, "Error creating thread %d\n", i);
      exit(1);
    }
  }

  for(int i = 0; i < numThreads; i++) pthread_join(workers[i], NULL);
}

