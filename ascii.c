#include <stdio.h>
#include <stdlib.h>
#include "mandelbrot.h"

const int precision = 32;
const int width =  120;
const int height = 30;
const char color[] = " .:-=+*#%@";

void drawPixel(double hue){
	int index = hue * 10;
	printf("%c", color[index]);
}

int main(){
	double** hues = calculateHues(width, height, precision);
	for(int y = 0; y < height; y++){
		for(int x = 0; x < width; x++)
				drawPixel(hues[y][x]);
		free(hues[y]);
		printf("\n");
	}
	free(hues);
	return 0;
}
