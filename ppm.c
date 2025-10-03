#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include "mandelbrot.h"

const int precision = 32;
const int width =  900;
const int height = 600;

uint8_t* hueToRgb(double hue){
	uint8_t* result = malloc(3 * sizeof(uint8_t));
	if(hue == 0.9){
		result[0] = 0; result[1] = 0; 	result[2] = 0; 
		return result;
	}
	int H = hue * 360;
	uint8_t X = (1 - abs(((H/60)%2)-1))*255;
	//printf("%.2f  % 2d  % 2d\n", hue, H, X);

	if( 0 <= H && H < 60)
		result[0] = 255; result[1] = X; 	result[2] = 0; 
	if( 60 <= H && H < 120)
		result[0] = X; 	 result[1] = 255;	result[2] = 0; 
	if( 120 <= H && H < 180)
		result[0] = 0; 	 result[1] = 255;	result[2] = X; 
	if( 180 <= H && H < 240)
		result[0] = 0; 	 result[1] = X; 	result[2] = 255; 
	if( 240 <= H && H < 300)
		result[0] = X; 	 result[1] = 0; 	result[2] = 255; 
	if( 300 <= H && H < 360)
		result[0] = 255; result[1] = 0; 	result[2] = X; 

	//printf("%02x %02x %02x\n", result[0], result[1], result[2]);
	return result;
}

void writePixel(double hue, FILE* output){
	uint8_t* bytes = hueToRgb(hue);
	fwrite(bytes, sizeof(uint8_t), 3, output);
	free(bytes);
}

int main(){
	double** hues = calculateHues(width, height, precision);
	FILE* output = fopen("mandelbrot.ppm", "w");
	fprintf(output, "P6\n%d %d\n255\n", width, height);
	fclose(output);
	output = fopen("mandelbrot.ppm", "ab");
	for(int y = 0; y < height; y++){
		for(int x = 0; x < width; x++)
				writePixel(hues[y][x], output);
		free(hues[y]);
	}
	fclose(output);
	free(hues);
	return 0;
}
