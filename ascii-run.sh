#!/bin/bash
gcc mandelbrot.c mandelbrot.h ascii.c -o ascii -lm -O3 && ./ascii;
