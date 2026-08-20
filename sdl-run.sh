#!/bin/bash
if [ ! -d out ] ; then
	mkdir out;
fi
gcc mandelbrot.c color.c sdl.c -lSDL2 -lm -o out/sdl -O3 "$@" && out/sdl;
