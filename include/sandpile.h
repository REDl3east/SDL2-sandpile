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
  void input(int round);

 private:
  int* const sandpile;
  std::barrier<>* barrier;
  std::thread* threads;
  int n_threads;
  bool started = false;
  static constexpr auto MULTIPLE = 5;
  bool mouse_down = false;
  std::atomic_bool do_close = false;
  bool pause_render = false;
};

#endif