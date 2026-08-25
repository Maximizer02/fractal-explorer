typedef enum {
  MANDELBROT,
  JULIA,
  BURNING_SHIP
} Fractal;

double** calculateHues(int width, int height,
    double xOffset, double yOffset,
    int precision, Fractal type, double angle);
