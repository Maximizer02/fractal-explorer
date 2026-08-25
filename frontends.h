typedef enum {
  ASCII,
  PPM,
  SDL
} Frontend;

void ascii_main(double** hues, int width, int height, bool color, bool block);
void ppm_main(double** hues, int width, int height, char* filename);
void sdl_main(double** hues, int width, int height);
