#!/bin/bash
if [ ! -d out ] ; then
	mkdir out;
fi
gcc mandelbrot.c mandelbrot.h sdl.c -lSDL2 -o out/sdl -O3 "$@" && out/sdl;
