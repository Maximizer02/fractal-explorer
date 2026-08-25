# Fractal Explorer
Simple command line utility to generate visualizations of various escape-time fractals.

## Fractals
Currently these 3 Fractals are supported:
- Mandelbrot set
- Julia set
- Burning Ship fractal

## Frontends
The application has 3 ways to visualize the fractals:
- In a Window using SDL2
- As an image in the PPM format
- As ASCII Art
The default is the SDL2 frontend, the other visualizations can be activated via CLI options.
Currently its non-interactive, but this may change in the future.

## CLI options
- `-a` Set visualization to ASCII.
- `-h <int>` Height of the displayed output.
- `-i` Set visualization to image.
- `-p <int>` Precision or max. number of iterations. Higher values are slower.
- `-r <double>` Radian offset. Only used with the Julia set.
- `-t <type>` Choose what fractal you want to view. Allowed values are `mandelbrot`, `julia` and `burningship`. Defaults to `mandelbrot`.
- `-w <int>` Width of the displayed output.

## Planned CLI options
- `-b` Use block characters for output. Only used with ASCII frontend.
- `-c` Colorize output. Only used with ASCII frontend.
- `-g` Make output Grayscale.
- `-o <string>` Output filename. Only used with PPM frontend.
- `-x <double>` X offset.
- `-y <double>` Y offset.
- `-z <double>` Zoom.

## Dependencies
- gcc
- Bash or any other POSIX compliant shell
- SDL2

## References
- [Mandelbrot set](https://en.wikipedia.org/wiki/Mandelbrot_set)
- [Julia set](https://en.wikipedia.org/wiki/Julia_set)
- [Burning Ship fractal](https://en.wikipedia.org/wiki/Burning_Ship_fractal)
- [PPM image format](https://en.wikipedia.org/wiki/Netpbm)
- [HSV to RGB conversion](https://www.rapidtables.com/convert/color/hsv-to-rgb.html)
