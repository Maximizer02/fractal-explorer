#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "color.h"

const char symbols[] = " .:-=+*#%@";

void drawPixel(double hue, bool color, bool block){
	char symbol = symbols[(int)(10 * hue)];
  if(color){
    RGB rgb = hueToRgb(hue);
    if(block)
      printf("\x1b[38;2;%d;%d;%dm█\x1b[0m", rgb.R, rgb.G, rgb.B);
    else
      printf("\x1b[38;2;%d;%d;%dm%c\x1b[0m", rgb.R, rgb.G, rgb.B, symbol);
  } else
    if(block)
      printf(symbol == ' ' ? " ": "█");
    else
      printf("%c", symbol);
}

void ascii_main(double** hues, int width, int height, bool color, bool block){
	for(int y = 0; y < height; y++){
		for(int x = 0; x < width; x++)
				drawPixel(hues[y][x], color, block);
		printf("\n");
	}
}
