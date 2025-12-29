#!/bin/bash
if [ ! -d out ] ; then
	mkdir out;
fi
gcc mandelbrot.c mandelbrot.h ppm.c -o out/ppm -O3 \
	&& out/ppm \
	&& mv mandelbrot.ppm out/ \
	&& ffplay out/mandelbrot.ppm;
