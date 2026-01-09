#include <math.h>
#include <stdlib.h>
#include "mandelbrot.h"

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
	double newX = (p.x * p.x) - (p.y * p.y);
	double newY = 2.0 * p.x * p.y;
	return (Point){.x = newX, .y = newY};
}

Point mapSpace(int x, int y, int width, int height){
	#ifdef julia 
		double newX = (3.0 / width  * x) - 1.5;
	#else
		double newX = (3.0 / width  * x) - 2.0;
	#endif /* julia */
	double newY = (2.0 / height * y) - 1.0;
	return (Point){.x = newX, .y = newY};
}

double calculatePixel(Point p, int precision){
	Point z = {.x = p.x, .y = p.y};
	#ifdef julia
		p = (Point){.x = -0.5125, .y = 0.5213};
	#endif  /* julia */
	for(int i = 0; i < precision; i++){
		z = CAdd(CSquare(z), p);
		double length = CLength(z);
		if(length >= 2.0)
			return (double) i / precision;
	}
	return 0.99;
}

double** calculateHues(int width, int height, int precision){
	#ifdef prec
		precision = prec;
	#endif
	double** result = malloc(sizeof(double*) * height); 
	for(int y = 0; y < height; y++){
		result[y] = malloc(sizeof(double) * width);
		for(int x = 0; x < width; x++){
			Point p = mapSpace(x, y, width, height);
			result[y][x] = calculatePixel(p, precision);
		}
	}
	return result;
}
