
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../headers/stb_image_write.h"

#include <stdlib.h>
#include <math.h>

#include "../headers/image_proc.h"

unsigned char* rgb_from_iteration(int intensity, int max_inter) {
  unsigned char* color = (unsigned char*)malloc(3 * sizeof(unsigned char));

  unsigned char red, green, blue; 

  red   = intensity;
  green = intensity;
  blue  = intensity;

  color[0] = red; color[1] = green; color[2] = blue;
  return color;
}

void write_PNG(int* data, int width, int height, const char *filename, int max_inter){ 

  unsigned char* image_data = (unsigned char*) malloc(width * height * 3 * sizeof(unsigned char));
  
  for(int i = 0; i < width*height; i++){

    float mapped = pow( fminf((float)max_inter, (float)data[i]/256.f), 0.5f);
    unsigned char result = (unsigned char)(255.f * mapped);
    
    unsigned char* color = rgb_from_iteration(result, max_inter);
  
    image_data[i*3]   = color[0];
    image_data[i*3+1] = color[1];
    image_data[i*3+2] = color[2];
  }

  if(!stbi_write_png("mandelbrot.png", width, height, 3, image_data, width * 3)) {
    fprintf(stderr, "Error writing image to file\n");
    free(image_data);
    return;
  }

  free(image_data);
  printf("Mandelbrot set rendered successfully!\n"); 
}
