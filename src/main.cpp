#include <SDL.h>

const int square_size = 40;
const int WINDOW_WIDTH = 32*square_size;
const int WINDOW_HEIGHT = 18*square_size;
const int grid_size = (WINDOW_WIDTH*WINDOW_HEIGHT/(square_size*square_size));


struct Node {
    bool blocked;
    SDL_Rect transform;
};

struct v2 {
    int x, y;
};

Node grid[grid_size] = {};

Node start_stop_nodes[2] = {{true, {square_size*5, square_size*5, square_size, square_size}}, {true, {square_size*6, square_size*5, square_size, square_size}}}; // first is start, second is end

Node open_list[grid_size] = {};
Node closed_list[grid_size] = {};


Node get_node_from_grid(int x, int y) {
    for(Node n : grid) {
        if(x >= n.transform.x && x < n.transform.x+square_size && y >= n.transform.y && y < n.transform.y+square_size) {
            return n;
        }
    }
    return {0, 0, 0, 0};
}

int get_node_index(Node node) {
    int i = 0;
    for(Node n : grid) {
        if(n.transform.x == node.transform.x && n.transform.y == node.transform.y) {
            return i;
        }
        i++;
    }
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
        }
    }
    
    open_list[get_node_index(start_stop_nodes[0])] = start_stop_nodes[0];
    
    // TODO(William-hogfeldt): Develop the algo implementation using this
    // https://www.edureka.co/blog/a-search-algorithm/
    bool found_path = true;
    while(!found_path) {
        int f_values[grid_size];
        
    }
    
    // SDL initialization stuff
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window *window = SDL_CreateWindow("GAME", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
    
    bool quit = false;
    bool drawing_blocks = false;
    int mouseX, mouseY;
    int start_stop_index = 0;
    while(!quit) {
        // update mouse pos
        SDL_GetMouseState(&mouseX, &mouseY);
        
        SDL_Event e;
        while( SDL_PollEvent( &e ) != 0 )
        {
            //User requests quit
            if( e.type == SDL_QUIT ) quit = true;
            else if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT) drawing_blocks = true;
            else if (e.type == SDL_MOUSEBUTTONUP && e.button.button == SDL_BUTTON_LEFT) drawing_blocks = false;
            else if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_RIGHT) {
                Node mouse_node = get_node_from_grid(mouseX, mouseY);
                start_stop_nodes[start_stop_index].transform.x = mouse_node.transform.x;
                start_stop_nodes[start_stop_index].transform.y = mouse_node.transform.y;
                start_stop_index = start_stop_index ^ 1; 
            }
        }
        
        // Paint blocked blocks
        if (drawing_blocks) {
            Node node = get_node_from_grid(mouseX, mouseY);
            grid[get_node_index(node)].blocked = true;
        }
        
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
        for (int i = 0; i < 2; i += 1){
            if(i == 0) {
                SDL_SetRenderDrawColor(renderer, 100, 100, 200, 255);
            } else {
                SDL_SetRenderDrawColor(renderer, 159, 43, 104, 255);
            }
            SDL_RenderFillRect(renderer, &start_stop_nodes[i].transform);
        }
        
        SDL_RenderPresent(renderer);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    }
    
    return 0;
}