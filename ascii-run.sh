#!/bin/bash
gcc mandelbrot.c mandelbrot.h ascii.c -o out/ascii -lm -O3 && out/./ascii;
