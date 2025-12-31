#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "mandelbrot.h"

const int  precision = 32;
const int  width =  800;
const int  height = 600;
const char filename[] = "mandelbrot.ppm";

typedef struct RGB {
	uint8_t R;
	uint8_t G;
	uint8_t B;
} RGB;

RGB hueToRgb(double hue){
	int H = hue * 360;
	uint8_t X = (1 - abs(((H / 60) % 2) - 1)) * 255;
	if(hue == 0.99)			 return (RGB){.R =   0, .G =   0, .B =   0};
	if(   0 <= H && H <  60) return (RGB){.R = 255, .G =   X, .B =   0};
	if(  60 <= H && H < 120) return (RGB){.R =   X, .G = 255, .B =   0};
	if( 120 <= H && H < 180) return (RGB){.R =   0, .G = 255, .B =   X};
	if( 180 <= H && H < 240) return (RGB){.R =   0, .G =   X, .B = 255};
	if( 240 <= H && H < 300) return (RGB){.R =   X, .G =   0, .B = 255};
	if( 300 <= H && H < 360) return (RGB){.R = 255, .G =   0, .B =   X};
	return (RGB){.R = 0, .G = 0, .B = 0};
}

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
