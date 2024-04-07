
#ifndef IMAGE_PROC
#define IMAGE_PROC

unsigned char* rgb_from_iteration(int intensity, int max_inter);
void write_PNG(int* data, int width, int height, const char *filename, int max_inter);

#endif

