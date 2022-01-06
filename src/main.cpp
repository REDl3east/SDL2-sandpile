#include "main.h"

static constexpr int INITIAL_WINDOW_WIDTH = 1280;
static constexpr int INITIAL_WINDOW_HEIGHT = 720;
static constexpr int WORLD_WIDTH = 500;
static constexpr int WORLD_HEIGHT = 500;
static constexpr const char *APP_NAME = "SDL Sandpile";

int main(int argc, char *argv[]) {
  if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
    std::cout << "Failed to initialize SDL: " << SDL_GetError() << "\n";
    return 1;
  }

  std::shared_ptr<SDL_Window> window(SDL_CreateWindow(APP_NAME, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, INITIAL_WINDOW_WIDTH, INITIAL_WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE), [](auto *p) { SDL_DestroyWindow(p); });
  if(!window){
    std::cout << "Failed to create window: " << SDL_GetError() << "\n";
    return 1;
  }
  
  std::shared_ptr<SDL_Renderer> renderer(SDL_CreateRenderer(window.get(), -1, 0), [](auto *p) { SDL_DestroyRenderer(p); });
    if(!renderer){
    std::cout << "Failed to create renderer: " << SDL_GetError() << "\n";
    return 1;
  }
  Sandpile world(renderer, INITIAL_WINDOW_WIDTH, INITIAL_WINDOW_HEIGHT, WORLD_WIDTH, WORLD_HEIGHT);

  world.set_colors(
    {.r = 255, .g = 255, .b = 255}, // 0 grains
    {.r = 0,   .g = 255, .b = 0},   // 1 grains
    {.r = 128, .g = 0,   .b = 128}, // 2 grains
    {.r = 255, .g = 215, .b = 0},   // 3 grains
    {.r = 255, .g = 255, .b = 255}  // > 3 grains
  );

  world.add_sand(world.width()/2, world.height() / 2, 1000000);


  world.start(6);
  world.join();

  SDL_Quit();
  return 0;
}
