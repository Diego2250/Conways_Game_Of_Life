#include <iostream>
#include <fstream>
#include <SDL.h>
#include <vector>

// Define the size of the framebuffer
const int FRAMEBUFFER_WIDTH = 80;
const int FRAMEBUFFER_HEIGHT = 80;
const int FRAMEBUFFER_SIZE = FRAMEBUFFER_WIDTH * FRAMEBUFFER_HEIGHT;
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 800;

// Function to apply the rules of Conway's Game of Life and update the framebuffer
void updateGameOfLife();

// Define an initial pattern
void setInitialPattern();

// Define a Color struct to hold the RGB values of a pixel
struct Color {
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
};

// Declare the framebuffer as a global variable
Color framebuffer[FRAMEBUFFER_SIZE];

// Declare a global clearColor of type Color
Color clearColor = {0, 0, 0, 255}; // Initially set to black

// Declare a global currentColor of type Color
Color currentColor = {255, 255, 255, 255}; // Initially set to white

int x = 10;
int y = 10;

// Function to clear the framebuffer with the clearColor
void clear() {
    for (int i = 0; i < FRAMEBUFFER_SIZE; i++) {
        framebuffer[i] = clearColor;
    }
}

// Function to set a specific pixel in the framebuffer to the currentColor
void point(int x, int y) {
    if (x >= 0 && x < FRAMEBUFFER_WIDTH && y >= 0 && y < FRAMEBUFFER_HEIGHT) {
        framebuffer[y * FRAMEBUFFER_WIDTH + x] = currentColor;
    }
}

void renderBuffer(SDL_Renderer* renderer) {
    // Create a texture
    SDL_Texture* texture = SDL_CreateTexture(
            renderer,
            SDL_PIXELFORMAT_ABGR8888,
            SDL_TEXTUREACCESS_STREAMING,
            FRAMEBUFFER_WIDTH,
            FRAMEBUFFER_HEIGHT
    );

    // Update the texture with the pixel data from the framebuffer
    SDL_UpdateTexture(
            texture,
            NULL,
            framebuffer,
            FRAMEBUFFER_WIDTH * sizeof(Color)
    );

    // Copy the texture to the renderer
    SDL_RenderCopy(renderer, texture, NULL, NULL);

    // Destroy the texture
    SDL_DestroyTexture(texture);
}

void render(SDL_Renderer* renderer) {
    // Clear the framebuffer
    // clear();

    // Draw a point
    point(x++, y++);

    // Render the framebuffer to the screen
    renderBuffer(renderer);
}

int SDL_main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window* window = SDL_CreateWindow("life", 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0);

    SDL_Renderer* renderer = SDL_CreateRenderer(
            window,
            -1,
            SDL_RENDERER_ACCELERATED
    );

    // Set the initial pattern
    setInitialPattern();

    bool running = true;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        // Update the game state based on Conway's Game of Life rules
        updateGameOfLife();

        // Call our render function
        render(renderer);

        // Present the frame buffer to the screen
        SDL_RenderPresent(renderer);

        // Delay to limit the frame rate
        SDL_Delay(1000 / 10); // Adjust the delay here (e.g., 1000 ms / 10 = 100 ms per frame)
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

int countLiveNeighbors(int x, int y) {
    int liveNeighbors = 0;
    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            if (dx == 0 && dy == 0) continue; // Skip the cell itself
            int nx = x + dx;
            int ny = y + dy;
            if (nx >= 0 && nx < FRAMEBUFFER_WIDTH && ny >= 0 && ny < FRAMEBUFFER_HEIGHT) {
                if (framebuffer[ny * FRAMEBUFFER_WIDTH + nx].r == 255) // Assuming white represents a live cell
                    liveNeighbors++;
            }
        }
    }
    return liveNeighbors;
}

// Function to apply the rules of Conway's Game of Life and update the framebuffer
void updateGameOfLife() {
    Color newFramebuffer[FRAMEBUFFER_SIZE];
    for (int y = 0; y < FRAMEBUFFER_HEIGHT; y++) {
        for (int x = 0; x < FRAMEBUFFER_WIDTH; x++) {
            int liveNeighbors = countLiveNeighbors(x, y);
            if (framebuffer[y * FRAMEBUFFER_WIDTH + x].r == 255) {
                // Live cell rules
                if (liveNeighbors < 2 || liveNeighbors > 3)
                    newFramebuffer[y * FRAMEBUFFER_WIDTH + x] = {0, 0, 0, 255}; // Die
                else
                    newFramebuffer[y * FRAMEBUFFER_WIDTH + x] = {255, 255, 255, 255}; // Survive
            } else {
                // Dead cell rules
                if (liveNeighbors == 3)
                    newFramebuffer[y * FRAMEBUFFER_WIDTH + x] = {255, 255, 255, 255}; // Reproduce
                else
                    newFramebuffer[y * FRAMEBUFFER_WIDTH + x] = {0, 0, 0, 255}; // Stay dead
            }
        }
    }
    // Update the framebuffer with the new state
    memcpy(framebuffer, newFramebuffer, sizeof(framebuffer));
}

int midX = FRAMEBUFFER_WIDTH / 2;
int midY = FRAMEBUFFER_HEIGHT / 2;

void setInitialPattern() {
    // Clear the framebuffer
    for (int i = 0; i < FRAMEBUFFER_SIZE; i++) {
        framebuffer[i] = clearColor;
    }

    // Glider pattern at the center
    point(midX, midY);
    point(midX + 1, midY);
    point(midX, midY + 1);
    point(midX - 1, midY + 1);
    point(midX, midY + 2);

    // Glider pattern at the top-left corner
    point(midX - 15, midY - 15);
    point(midX - 14, midY - 15);
    point(midX - 15, midY - 14);
    point(midX - 16, midY - 14);
    point(midX - 15, midY - 13);

    // Glider pattern at the bottom-right corner
    point(midX + 15, midY + 15);
    point(midX + 16, midY + 15);
    point(midX + 15, midY + 16);
    point(midX + 14, midY + 16);
    point(midX + 15, midY + 17);

    // Glider pattern at the top-right corner
    point(midX + 15, midY - 15);
    point(midX + 16, midY - 15);
    point(midX + 15, midY - 14);
    point(midX + 14, midY - 14);
    point(midX + 15, midY - 13);

    // Glider pattern at the bottom-left corner
    point(midX - 15, midY + 15);
    point(midX - 14, midY + 15);
    point(midX - 15, midY + 16);
    point(midX - 16, midY + 16);
    point(midX - 15, midY + 17);

}





