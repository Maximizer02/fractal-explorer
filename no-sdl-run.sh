#!/bin/bash
if [ ! -d out ] ; then
        mkdir out;
fi

gcc main.c fractal.c ascii.c color.c ppm.c sdl.c \
  -Dno_sdl \
  -lm \
  -o out/bin-no-sdl && \
out/bin-no-sdl "$@"
