typedef enum {
  MANDELBROT,
  JULIA,
  BURNING_SHIP
} Fractal;

double** calculateHues(int width, int height, int precision, Fractal type, double angle);
