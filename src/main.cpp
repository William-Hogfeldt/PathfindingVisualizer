#include <SDL.h>

const int WINDOW_WIDTH = 1920;
const int WINDOW_HEIGHT = 1080;
const int square_size = 40;
const int grid_size = (WINDOW_WIDTH*WINDOW_HEIGHT/(square_size*square_size));


struct Node {
    bool blocked;
    SDL_Rect transform;
};

struct v2 {
    int x, y;
};

Node grid[grid_size] = {};
v2 blocked_positions[] = {{66, 66}, {106, 106}};

// TODO(william): Convert to from pixel to grid position function kind of
Node get_node_from_grid(int x, int y) {
    for(Node n : grid) {
        if(x >= n.transform.x && x < n.transform.x+40 && y >= n.transform.y && y < n.transform.y+40) {
            return n;
        }
    }
    return {0, 0, 0, 0};
}

int main(int argc, char *argv[])
{
    // TODO(William): Algorithm
    const int grid_size_x = grid_size/(WINDOW_HEIGHT/square_size);
    const int grid_size_y = grid_size/grid_size_x;
    
    // Create grid
    for (int i = 0; i < WINDOW_HEIGHT/square_size; i += 1){
        for (int j = 0; j < WINDOW_WIDTH/square_size; j += 1){
            grid[i*WINDOW_WIDTH/square_size+j].transform = {j*square_size, i*square_size, square_size, square_size};
            for(v2 bp : blocked_positions) {
                if(bp.x >= grid[i*WINDOW_WIDTH/square_size+j].transform.x && bp.x < grid[i*WINDOW_WIDTH/square_size+j].transform.x+40 && bp.y >= grid[i*WINDOW_WIDTH/square_size+j].transform.y && bp.y < grid[i*WINDOW_WIDTH/square_size+j].transform.y+40) {
                    grid[i*WINDOW_WIDTH/square_size+j].blocked = true;
                }
            }
        }
    }
    
    // SDL initialization stuff
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window *window = SDL_CreateWindow("GAME", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
    
    int i = 0;
    
    while(1) {
        // TODO(william): Handle left click to add to blocked array
        
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        for (Node n : grid){
            if(n.blocked) { 
                SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
                SDL_RenderFillRect(renderer, &n.transform);
            } else {
                SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
                SDL_RenderDrawRect(renderer, &n.transform);
            }
        }
        SDL_RenderPresent(renderer);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    }
    
    return 0;
}