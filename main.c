#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "frontends.h"
#include "mandelbrot.h"

#define optstring "w:h:x:y:z:p:ait:"

typedef enum {
  MANDELBROT,
  JULIA,
  BURNING_SHIP
} Fractal;

Fractal getFractalType(char* str){
  if (strcmp(optarg, "mandelbrot") == 0) return MANDELBROT;
  if (strcmp(optarg, "julia") == 0) return JULIA;
  if (strcmp(optarg, "burningship") == 0) return BURNING_SHIP;
  exit(1);
}

int main(int argc, char** argv){
  int opt;

  int width  = 800;
  int height = 600;
  int xOffset = 0;
  int yOffset = 0;
  double zoom = 1.0;
  int precision = 32;

  bool ascii = false;
  bool image = false;

  Fractal fractal = MANDELBROT;

  while((opt = getopt(argc, argv, optstring)) != -1){
    switch(opt){
      case 'w':
        width = atoi(optarg);
        break;
      case 'h':
        height = atoi(optarg);
        break;
      case 'x':
        xOffset = atoi(optarg);
        break;
      case 'y':
        yOffset = atoi(optarg);
        break;
      case 'z':
        zoom = 1.0 / (double) atoi(optarg);
        break;
      case 'p':
        precision = atoi(optarg);
        break;
      case 'a':
        width = 120;
        height = 30;
        ascii = true;
        break;
      case 'i':
        image = true;
        break;
      case 't':
        fractal = getFractalType(optarg);
        break;
      default:
        return 1;
    }
  }

  double** hues;
  switch(fractal){
    case MANDELBROT:
      hues = calculateHues(width, height, precision);
      break;
    case JULIA:
    case BURNING_SHIP:
      return 1;
  }

  if(ascii)
    ascii_main(hues, width, height);

  if(image)
    ppm_main(hues, width, height);

  if(!ascii && !image)
    sdl_main(hues, width, height);

  for(int i = 0; i < height; i++)
    free(hues[i]);
  free(hues);
  return 0;
}
