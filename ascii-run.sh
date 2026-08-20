#!/bin/bash
if [ ! -d out ] ; then
	mkdir out;
fi
gcc mandelbrot.c color.c ascii.c -lm -o out/ascii -O3 "$@" && out/ascii;
