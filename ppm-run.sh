#!/bin/bash
if [ ! -d out ] ; then
	mkdir out;
fi
gcc mandelbrot.c color.c ppm.c -lm -o out/ppm -O3 "$@" \
	&& out/ppm \
	&& mv mandelbrot.ppm out/ \
	&& ffplay out/mandelbrot.ppm;
