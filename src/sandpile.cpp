#include "sandpile.h"

Sandpile::Sandpile(std::shared_ptr<SDL_Renderer> renderer, int window_width, int window_height, int width, int height) : PixelWorld(renderer, window_width, window_height, width, height), sandpile(new int[width * height]) {
  for (int i = 0; i < width; i++) {
    for (int j = 0; j < height; j++) {
      sandpile[i * height + j] = 0;
    }
  }
}

Sandpile::~Sandpile() {
  delete[] sandpile;
  if (barrier != nullptr) delete barrier;
  if (threads != nullptr) delete[] threads;
}

void Sandpile::set_sand(int x, int y, int amount) {
  sandpile[x * m_height + y] = amount;
}

void Sandpile::add_sand(int x, int y, int amount) {
  sandpile[x * m_height + y] += amount;
}

int Sandpile::get_sand_count(int x, int y) {
  return sandpile[x * m_height + y];
}

bool Sandpile::start(int n) {
  if (started) return false;
  if (n <= 0) return false;

  n_threads = n;

  barrier = new std::barrier<>(n_threads);
  threads = new std::thread[n_threads];

  for (int i = 0; i < n_threads; i++) {
    threads[i] = std::thread(std::bind(&Sandpile::worker, this, i));
  }
  started = true;
  return true;
}

bool Sandpile::join() {
  if (!started) return false;
  for (int i = 0; i < n_threads; i++) {
    threads[i].join();
  }
  started = false;
  delete barrier;
  barrier = nullptr;
  delete[] threads;
  threads = nullptr;
  return true;
}

void Sandpile::worker(int id) {
  int regular_block_size = m_width / n_threads;
  int block_size = (id == n_threads - 1) ? regular_block_size + m_width % n_threads : regular_block_size;
  int start_index = id * regular_block_size;
  int end_index = start_index + block_size;
  int round = 0;

  auto check = [&](int x, int y, int increment) {
    int index = x * m_height + y;
    sandpile[index] += increment;
    switch (sandpile[index]) {
      case 0: {
        point(x, y, 255, 0, 255);
        break;
      }
      case 1: {
        point(x, y, 255, 111, 111);
        break;
      }
      case 2: {
        point(x, y, 54, 200, 25);
        break;
      }
      case 3: {
        point(x, y, 55, 88, 175);
        break;
      }
      default: {
        point(x, y, 192, 192, 192);
        break;
      }
    }
  };

  while (1) {
    for (int i = start_index; i < end_index; i++) {
      int start = ((i * 2 + round) % m_height);
      int total = 0;
      for (int j = start; total < m_height / MULTIPLE; j = (j + MULTIPLE) % m_height) {
        if (sandpile[i * m_height + j] >= 4) {
          if (i - 1 >= 0) {
            check((i - 1), j, 1);
          }
          if (i + 1 < m_width) {
            check((i + 1), j, 1);
          }
          if (j - 1 >= 0) {
            check(i, (j - 1), 1);
          }
          if (j + 1 < m_height) {
            check(i, (j + 1), 1);
          }
          check(i, j, -4);
        }
        total++;
      }
    }

    round++;

    barrier->arrive_and_wait();
    if (id == n_threads - 1) input(round);
    barrier->arrive_and_wait();

    if (do_close.load()) break;
  }
}
void Sandpile::input(int round) {
  SDL_Event event;
  int ret = SDL_PollEvent(&event);
  if (ret) {
    switch (event.type) {
      case SDL_QUIT: {
        do_close.store(true);
        break;
      }
      case SDL_KEYDOWN: {
        if (event.key.keysym.sym == SDLK_p) {
          pause_render = !pause_render;
        }
        if (event.key.keysym.sym == SDLK_s) {
          time_t rawtime;
          struct tm* timeinfo;
          char buffer[80];

          time(&rawtime);
          timeinfo = localtime(&rawtime);

          strftime(buffer, sizeof(buffer), "%d-%m-%Y %H:%M:%S", timeinfo);
          std::string str(buffer);
          save("/home/dalton/Desktop/sandpiles/" + str + ".png");
        }
        break;
      }
      case SDL_MOUSEBUTTONDOWN: {
        if (event.button.button == SDL_BUTTON_LEFT) {
          mouse_down = true;
        }
        break;
      }
      case SDL_MOUSEBUTTONUP: {
        if (event.button.button == SDL_BUTTON_LEFT) {
          mouse_down = false;
        }
        break;
      }
      case SDL_MOUSEMOTION: {
        if (mouse_down) {
          update_position(event.motion.xrel, event.motion.yrel);
        }
        break;
      }
      case SDL_MOUSEWHEEL: {
        int mousex, mousey;
        SDL_GetMouseState(&mousex, &mousey);
        if (event.wheel.y > 0) {  //up
          zoom_in(mousex, mousey);
        } else if (event.wheel.y < 0) {  //down
          zoom_out(mousex, mousey);
        }
        break;
      }
    }
  }

  if (!pause_render && (round % 100 == 0)) {
    SDL_RenderClear(m_renderer.get());

    render();

    SDL_RenderPresent(m_renderer.get());
  }
}