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

  static constexpr uint8_t colors[5][3] = {{255, 0, 255}, {255, 111, 111}, {54, 200, 25}, {55, 88, 175}, {192, 192, 192}};
  const std::string save_path = "/home/dalton/Desktop/sandpiles/";
};

#endif