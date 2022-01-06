#ifndef SANDPILE_H
#define SANDPILE_H

#include <barrier>
#include <ctime>
#include <functional>
#include <iostream>
#include <thread>

#include "pixelWorld.h"

class Sandpile : public PixelWorld {
 public:
  Sandpile(std::shared_ptr<SDL_Renderer> renderer, int window_width, int window_height, int width, int height);
  ~Sandpile();

  void set_sand(int x, int y, int amount);
  void add_sand(int x, int y, int amount);
  int get_sand_count(int x, int y);
  bool start(int n);
  bool join();
  void worker(int id);
  void main_input_render(int round);
  void edit_input_render();
  void set_point(int x, int y, int increment=0);

  void set_colors(SDL_Color c1, SDL_Color c2,SDL_Color c3, SDL_Color c4, SDL_Color c5){
    colors[0] = c1;
    colors[1] = c2;
    colors[2] = c3;
    colors[3] = c4;
    colors[4] = c5;   
    for (int i = 0; i < width(); i++) {
      for (int j = 0; j < height(); j++) {
        sandpile[i * height() + j] = 0;
        set_point(i, j);
      }
    }
  }

  bool save_sandpile();

 private:
  int* const sandpile;
  std::barrier<>* barrier;
  std::thread* threads;
  int n_threads;
  bool started = false;
  static constexpr auto MULTIPLE = 5;
  bool mouse_down = false;
  bool lctrl_down = false;
  bool rctrl_down = false;
  std::atomic_bool do_close = false;
  bool pause_render = false;

  SDL_Color colors[5] = {
    {.r = 255, .g = 0, .b = 255},
    {.r = 255, .g = 111, .b = 111},
    {.r = 54, .g = 200, .b = 25},
    {.r = 55, .g = 88, .b = 175},
    {.r = 192, .g = 192, .b = 192},
  };
  const std::string save_path = "./";
};

#endif