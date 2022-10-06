
#include <SDL.h>
#include <stdlib.h>

const int SQUARE_SIZE = 40;
const int WINDOW_WIDTH = 720;
const int WINDOW_HEIGHT = 576;

struct Node {
    bool blocked;
    int x, y, f_cost, g_cost, h_cost;
};

Node node_array[WINDOW_WIDTH*WINDOW_HEIGHT/SQUARE_SIZE] = {};

int main(int argv, char **args) {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow("AStar", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    
    bool quit = false;
    while(!quit) {
        int mouse_x, mouse_y, start_or_stop = 0;
        bool draw_blocks, draw_start_stop = false;
        SDL_GetMouseState(&mouse_x, &mouse_y);
        SDL_Event e;
        while (SDL_PollEvent(&e))
        {
            switch (e.type)
            {
                case SDL_QUIT:
				quit = true;
                break;
                case SDL_MOUSEBUTTONDOWN:
                if (e.button.button == SDL_BUTTON_LEFT) draw_blocks = true;
                else if (e.button.button == SDL_BUTTON_RIGHT) draw_start_stop = true;
                break;
            }
        }
        
        SDL_SetRenderDrawColor(renderer,0,0,0,255);
        SDL_RenderClear(renderer);
        
        // Update grid
        for(int i; i < WINDOW_WIDTH*WINDOW_HEIGHT/SQUARE_SIZE; i++) {
            
        }
        
        SDL_RenderPresent(renderer);
    }
    
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}