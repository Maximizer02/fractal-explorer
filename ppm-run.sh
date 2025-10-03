#!/bin/bash
gcc mandelbrot.c mandelbrot.h ppm.c -o ppm -lm -O3 && ./ppm;
