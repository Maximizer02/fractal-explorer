#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <stdbool.h>
#include <stdio.h>
#include "color.h"
#include "mandelbrot.h"

#define WIDTH 800
#define HEIGHT 600

SDL_Window *window;
SDL_Renderer *renderer;
SDL_Texture *texture;
SDL_Event event;

int buffer[WIDTH * HEIGHT] = {0};
bool running = true;

void Init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("sdl init failed");
        exit(1);
    };

    window = SDL_CreateWindow("mandelbrot",
                              SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              WIDTH, HEIGHT,
                              SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, 0);

    SDL_RenderSetLogicalSize(renderer, WIDTH, HEIGHT);

    texture = SDL_CreateTexture(renderer,
                                SDL_PIXELFORMAT_RGBA32,
                                SDL_TEXTUREACCESS_STREAMING,
                                WIDTH, HEIGHT);

	double** hues = calculateHues(WIDTH, HEIGHT, 32);
	for(int h = 0 ; h< HEIGHT;h++)
		for(int w = 0 ; w< WIDTH;w++)
		{
			double hue = hues[h][w];
			RGB color = hueToRgb(hue);
			int colorValue;
			memcpy(&colorValue,&color,sizeof(RGB));
			buffer[(WIDTH*h) + w] = colorValue;
		}
    int texturePitch = 0;
    void *texturePixels = NULL;

    SDL_LockTexture(texture, NULL, &texturePixels, &texturePitch);
    memcpy(texturePixels, buffer, texturePitch * HEIGHT);
    SDL_UnlockTexture(texture);
}

void Update() {
    SDL_PollEvent(&event);
    if (event.type == SDL_QUIT)
        running = false;
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);
}

void Destroy() {
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

int main() {
    Init();
    while (running)
        Update();
    Destroy();
    return 0;
}
