#ifndef no_sdl
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <stdbool.h>
#include <stdio.h>
#include "color.h"

SDL_Window *window;
SDL_Renderer *renderer;
SDL_Texture *texture;
SDL_Event event;

int* buffer;
bool running = true;

void Init(double** hues, int width, int height, bool color) {
    buffer = malloc(width*height*sizeof(int));
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("sdl init failed");
        exit(1);
    };

    window = SDL_CreateWindow("Fractal Explorer",
                              SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              width, height,
                              SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, 0);

    SDL_RenderSetLogicalSize(renderer, width, height);

    texture = SDL_CreateTexture(renderer,
                                SDL_PIXELFORMAT_RGBA32,
                                SDL_TEXTUREACCESS_STREAMING,
                                width, height);

	for(int h = 0 ; h < height; h++)
		for(int w = 0 ; w < width; w++)
		{
			double hue = hues[h][w];
			RGB rgb;
      if(color)
        rgb = hueToRgb(hue);
      else
        rgb = (RGB){.R = 255*hue, .G = 255*hue, .B = 255*hue};
			int colorValue;
			memcpy(&colorValue,&rgb,sizeof(RGB));
			buffer[(width*h) + w] = colorValue;
		}
    int texturePitch = 0;
    void *texturePixels = NULL;

    SDL_LockTexture(texture, NULL, &texturePixels, &texturePitch);
    memcpy(texturePixels, buffer, texturePitch * height);
    SDL_UnlockTexture(texture);
}

void Update() {
    SDL_PollEvent(&event);
    if (event.type == SDL_QUIT || event.type == SDL_KEYDOWN)
        running = false;
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);
}

void Destroy() {
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    free(buffer);
    SDL_Quit();
}

void sdl_main(double** hues, int width, int height, bool color) {
    Init(hues, width, height, color);
    while (running)
        Update();
    Destroy();
}
#else
#include <stdlib.h>
#include <stdio.h>
void sdl_main(double** hues, int width, int height, bool color){
  printf("This binary was compiled without SDL2 support. Use another frontend.\n");
  exit(1);
}
#endif

