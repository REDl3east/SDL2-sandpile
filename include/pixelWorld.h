#ifndef PIXELWORLD_H
#define PIXELWORLD_H

#include <SDL.h>
#include <SDL_image.h>

#include <memory>
#include "lodepng.h"
class PixelWorld {
 public:
  PixelWorld(std::shared_ptr<SDL_Renderer> renderer, int window_width, int window_height, int width, int height);
  ~PixelWorld();

  void point(int x, int y, Uint8 r, Uint8 g, Uint8 b);
  void update_position(int xrel, int yrel);
  void zoom_in(int mousex, int mousey);
  void zoom_out(int mousex, int mousey);
  void render();

  int height() {
    return m_height;
  }
  int width() {
    return m_width;
  }

  bool save(const std::string &filename) {
    std::vector<unsigned char> image;
    image.resize(m_width * m_height * 4);

    int index = 0;
    for (unsigned y = 0; y < m_height; y++) {
      for (unsigned x = 0; x < m_width; x++) {
        image[4 * m_width * y + 4 * x + 0] = (m_pixels[index] >> 24) & 0xff;
        image[4 * m_width * y + 4 * x + 1] = (m_pixels[index] >> 16) & 0xff;
        image[4 * m_width * y + 4 * x + 2] = (m_pixels[index] >> 8) & 0xff;
        image[4 * m_width * y + 4 * x + 3] = 255;
        index++;
      }
    }

    unsigned error = lodepng::encode(filename, image, m_width, m_height);

    //if there's an error, display it
    if (error) {
      return false;
    }
    return true;
  }

 protected:
  int m_x, m_y, m_width, m_height;
  std::shared_ptr<SDL_Renderer> m_renderer;
  SDL_Texture *m_texture;
  SDL_Surface *m_surface;
  Uint32 *m_pixels;

 private:
  double m_scale = 1;
  static constexpr double zoom_scale = 1;
};

#endif