#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include "mandelbrot.h"

const int precision = 32;
const int width =  120;
const int height = 30;
const char symbols[] = " .:-=+*#%@";

#ifdef color
  typedef struct RGB {
    uint8_t R;
    uint8_t G;
    uint8_t B;
  } RGB;

  RGB hueToRgb(double hue){
    double H = hue * 360;
    uint8_t X = (1 - fabs( fmod((H / 60), 2) - 1)) * 255;
    if(hue == 0.99)			 return (RGB){.R =   0, .G =   0, .B =   0};
    if(   0 <= H && H <  60) return (RGB){.R = 255, .G =   X, .B =   0};
    if(  60 <= H && H < 120) return (RGB){.R =   X, .G = 255, .B =   0};
    if( 120 <= H && H < 180) return (RGB){.R =   0, .G = 255, .B =   X};
    if( 180 <= H && H < 240) return (RGB){.R =   0, .G =   X, .B = 255};
    if( 240 <= H && H < 300) return (RGB){.R =   X, .G =   0, .B = 255};
    if( 300 <= H && H < 360) return (RGB){.R = 255, .G =   0, .B =   X};
    return (RGB){.R = 0, .G = 0, .B = 0};
  }
#endif /* color */

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
