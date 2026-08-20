#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <math.h>
#include "mandelbrot.h"

#define WIDTH 800
#define HEIGHT 600

SDL_Window *window;
SDL_Renderer *renderer;
SDL_Texture *texture;
SDL_Event event;

int buffer[WIDTH * HEIGHT] = {0};
bool running = true;

typedef struct RGBA {
	uint8_t R;
	uint8_t G;
	uint8_t B;
	uint8_t A;
} RGBA;

RGBA hueToRgb(double hue){
	double H = hue * 360;
	uint8_t X = (1 - fabs( fmod((H / 60), 2) - 1)) * 255;
	if(hue == 0.99)			 return (RGBA){.R =   0, .G =   0, .B =   0};
	if(   0 <= H && H <  60) return (RGBA){.R = 255, .G =   X, .B =   0};
	if(  60 <= H && H < 120) return (RGBA){.R =   X, .G = 255, .B =   0};
	if( 120 <= H && H < 180) return (RGBA){.R =   0, .G = 255, .B =   X};
	if( 180 <= H && H < 240) return (RGBA){.R =   0, .G =   X, .B = 255};
	if( 240 <= H && H < 300) return (RGBA){.R =   X, .G =   0, .B = 255};
	if( 300 <= H && H < 360) return (RGBA){.R = 255, .G =   0, .B =   X};
	return (RGBA){.R = 0, .G = 0, .B = 0};
}

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
			RGBA color = hueToRgb(hue);
			int colorValue;
			memcpy(&colorValue,&color,sizeof(int));
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
