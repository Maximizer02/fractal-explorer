#!/bin/bash
if [ ! -d out ] ; then
	mkdir out;
fi
gcc mandelbrot.c mandelbrot.h ascii.c -o out/ascii -O3 $1 && out/ascii;
