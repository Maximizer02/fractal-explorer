#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "color.h"
#include "mandelbrot.h"

const int  precision = 32;
const int  width =  800;
const int  height = 600;
const char filename[] = "mandelbrot.ppm";

void writePixel(double hue, FILE* output){
	RGB rgb = hueToRgb(hue);
	fwrite(&rgb, sizeof(uint8_t), 3, output);
}

int main(){
	double** hues = calculateHues(width, height, precision);
	FILE* output = fopen(filename, "w");
	fprintf(output, "P6\n%d %d\n255\n", width, height);
	fclose(output);
	output = fopen(filename, "ab");
	for(int y = 0; y < height; y++){
		for(int x = 0; x < width; x++)
				writePixel(hues[y][x], output);
		free(hues[y]);
	}
	fclose(output);
	free(hues);
	return 0;
}
