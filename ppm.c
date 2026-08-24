#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "color.h"

const char filename[] = "mandelbrot.ppm";

void writePixel(double hue, FILE* output){
	RGB rgb = hueToRgb(hue);
	fwrite(&rgb, sizeof(uint8_t), 3, output);
}

void ppm_main(double** hues, int width, int height){
	FILE* output = fopen(filename, "w");
	fprintf(output, "P6\n%d %d\n255\n", width, height);
	fclose(output);
	output = fopen(filename, "ab");
	for(int y = 0; y < height; y++){
		for(int x = 0; x < width; x++)
				writePixel(hues[y][x], output);
	}
	fclose(output);
}
