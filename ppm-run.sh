#!/bin/bash
gcc mandelbrot.c mandelbrot.h ppm.c -o out/ppm -lm -O3 \
	&& out/./ppm \
	&& mv mandelbrot.ppm out/ \
	&& ffplay out/mandelbrot.ppm;
