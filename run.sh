#!/bin/bash
gcc main.c fractal.c ascii.c color.c ppm.c sdl.c \
  -lm \
  -lSDL2 \
  -o out/bin && \
out/bin "$@"
