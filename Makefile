
all:
	gcc src/main.c src/mandelbrot.c src/image_proc.c -o mandelbrot -lm
