#include "main.h"

static constexpr int INITIAL_WINDOW_WIDTH = 1280;
static constexpr int INITIAL_WINDOW_HEIGHT = 720;
static constexpr int WORLD_WIDTH = 500;
static constexpr int WORLD_HEIGHT = 500;
static constexpr const char *APP_NAME = "SDL Sandpile";

int main(int argc, char *argv[]) {
  if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't initialize SDL: %s", SDL_GetError());
    return 1;
  }

  std::shared_ptr<SDL_Window> window(SDL_CreateWindow(APP_NAME, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, INITIAL_WINDOW_WIDTH, INITIAL_WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE), [](SDL_Renderer *p) { SDL_DestroyWindow(p); });
  if(!window){
    std::cout << "Failed to create window: " << SDL_GetError() << "\n";
    return 1;
  }
  
  std::shared_ptr<SDL_Renderer> renderer(SDL_CreateRenderer(window.get(), -1, 0), [](SDL_Renderer *p) { SDL_DestroyRenderer(p); });
    if(!renderer){
    std::cout << "Failed to create renderer: " << SDL_GetError() << "\n";
    return 1;
  }
  Sandpile world(renderer, INITIAL_WINDOW_WIDTH, INITIAL_WINDOW_HEIGHT, WORLD_WIDTH, WORLD_HEIGHT);

  for (int i = 0; i < world.width(); i++) {
    for (int j = 0; j < world.height(); j++) {
      world.add_sand(i, j, 10);
    }
  }

  world.start(6);
  world.join();

  SDL_Quit();
  return 0;
}
