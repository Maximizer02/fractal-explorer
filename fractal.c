#include <math.h>
#include <stdlib.h>
#include "fractal.h"

typedef struct point {
	double x;
	double y;
} Point;

Point CAdd(Point a, Point b){
	double newX = a.x + b.x;
	double newY = a.y + b.y;
	return (Point){.x = newX, .y = newY};
}

double CLength(Point p){
	return sqrt(p.x * p.x + p.y * p.y);
}

Point CSquare(Point p){
  double x = p.x;
  double y = p.y;

	double newX = (x * x) - (y * y);
	double newY = 2.0 * x * y;
	return (Point){.x = newX, .y = newY};
}

Point mapSpace(int x, int y, int width, int height, double zoom, Fractal type){
	double newX = (3.0 / width  * x * zoom) - 2.0;
	double newY = (2.0 / height * y * zoom) - 1.0;

	if(type == JULIA){
		newX = (3.0 / width  * x * zoom) - 1.5;
  }

  if(type == BURNING_SHIP){
	  newX = (4.0 / width  * x * zoom) - 2.5;
	  newY = (3.0 / height * y * zoom) - 2.0;
  }

	return (Point){.x = newX, .y = newY};
}

Point mapAngle(double angle){
  return (Point){
    .x =  cos(angle),
    .y = -sin(angle)
  };
}

double calculatePixel(Point c, int precision, Fractal type, double angle){
	Point z = {.x = c.x, .y = c.y};
	if(type == JULIA){
      c = mapAngle(angle);
  }
	for(int i = 0; i < precision; i++){
    if(type == BURNING_SHIP){
      z.x = fabs(z.x);
      z.y = fabs(z.y);
    }
    z = CSquare(z);
		z = CAdd(z, c);
		double length = CLength(z);
		if(length >= 2.0)
			return (double) i / precision;
	}
	return 0.99;
}

double** calculateHues(
    int width, int height,
    double xOffset, double yOffset, double zoom,
    int precision, Fractal type, double angle){
	double** result = malloc(sizeof(double*) * height);
	for(int y = 0; y < height; y++){
		result[y] = malloc(sizeof(double) * width);
		for(int x = 0; x < width; x++){
			Point p = mapSpace(x, y, width, height, zoom, type);
      p = CAdd(p, (Point){.x = xOffset, .y = yOffset});
			result[y][x] = calculatePixel(p, precision, type, angle);
		}
	}
	return result;
}
