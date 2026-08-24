#include <stdio.h>
#include <stdlib.h>
#include "color.h"

const char symbols[] = " .:-=+*#%@";

void drawPixel(double hue){
	char symbol = symbols[(int)(10 * hue)];
  #ifdef color
    RGB rgb = hueToRgb(hue);
    #ifdef block
      printf("\x1b[38;2;%d;%d;%dm█\x1b[0m", rgb.R, rgb.G, rgb.B);
    #else
      printf("\x1b[38;2;%d;%d;%dm%c\x1b[0m", rgb.R, rgb.G, rgb.B, symbol);
    #endif /* block */
  #else
    #ifdef block
      printf(symbol == ' ' ? " ": "█");
    #else
      printf("%c", symbol);
    #endif /* block */
  #endif /* color */
}

void ascii_main(double** hues, int width, int height){
	for(int y = 0; y < height; y++){
		for(int x = 0; x < width; x++)
				drawPixel(hues[y][x]);
		printf("\n");
	}
}
