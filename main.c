#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "frontends.h"
#include "fractal.h"

#define optstring "w:h:x:y:z:p:ait:r:bcgo:"

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
  double xOffset = 0;
  double yOffset = 0;
  double zoom = 1.0;
  int precision = 32;
  double radians = 3.14;

  bool block = false;
  bool color = true;

  Fractal type = MANDELBROT;
  Frontend frontend = SDL;

  char* filename = NULL;

  char* eptr;

  while((opt = getopt(argc, argv, optstring)) != -1){
    switch(opt){
      case 'w':
        width = atoi(optarg);
        break;
      case 'h':
        height = atoi(optarg);
        break;
      case 'x':
        xOffset = strtod(optarg, &eptr);
        break;
      case 'y':
        yOffset = strtod(optarg, &eptr);
        break;
      case 'z':
        zoom = strtod(optarg, &eptr);
        break;
      case 'p':
        precision = atoi(optarg);
        break;
      case 'a':
        width = 120;
        height = 30;
        color = false;
        frontend = ASCII;
        break;
      case 'i':
        frontend = PPM;
        break;
      case 't':
        type = getFractalType(optarg);
        break;
      case 'r':
        radians = strtod(optarg, &eptr);
        break;
      case 'b':
        block = true;
        break;
      case 'c':
        color = true;
        break;
      case 'g':
        color = false;
        break;
      case 'o':
        int length = strlen(optarg)+1;
        filename = malloc(length);
        strncpy(filename, optarg, length-1);
        filename[length] = '\0';
        break;
      default:
        return 1;
    }
  }

  double** hues = calculateHues(width, height, xOffset, yOffset, precision, type, radians);

  switch(frontend){
    case ASCII:
      ascii_main(hues, width, height, color, block);
      break;
    case PPM:
      ppm_main(hues, width, height, color, filename);
      break;
    case SDL:
      sdl_main(hues, width, height, color);
      break;
  }

  for(int i = 0; i < height; i++)
    free(hues[i]);
  free(hues);
  if(filename != NULL)
    free(filename);
  return 0;
}
