#include <stdio.h>
#include <math.h>

const int width =  120;
const int height = 30;
const int prescision = 32;
const double xStep = 3.0 / width;
const double yStep = 2.0 / height;
const char color[] = " .:-=+*#%@";

typedef struct point {
	double x;
	double y;
} Point;

Point CAdd(Point a, Point b){
	double newX = a.x + b.x;
	double newY = a.y + b.y;
	Point result = {.x = newX, .y = newY};
	return result;
}

double CLength(Point p){
	double n = p.x * p.x + p.y * p.y;
	return sqrt(n);
}

Point CSquare(Point p){
	double newX = (p.x * p.x) - (p.y * p.y);
	double newY = 2.0 * p.x *p.y;
	Point result = {.x = newX, .y = newY};
	return result;
}

Point mapSpace(int x, int y){
	double newX = (xStep * x) - 2.0;
	double newY = (yStep * y) - 1.0;
	Point result = {.x = newX, .y = newY};
	return result;
}

double calculatePixel(Point p){
	Point z = {.x = p.x, .y = p.y};
	for(int i = 0; i < prescision; i++){
		z = CAdd(CSquare(z), p);
		double length = CLength(z);
		if(length >= 2.0)
			return (double) i / prescision;
	}
	return 0.9;
}

void drawPixel(double c){
	int index = c * 10;
	printf("%c", color[index]);
}

int main(){
	for(int y = 0; y < height; y++){
			for(int x = 0; x < width; x++){
				Point p = mapSpace(x,y);
				double color = calculatePixel(p);
				drawPixel(color);	
			}
			printf("\n");
		}
	return 0;
}
