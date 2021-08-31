#include "pixelWorld.h"

PixelWorld::PixelWorld(std::shared_ptr<SDL_Renderer> renderer, int window_width, int window_height, int width, int height) {
  m_x = window_width / 2 - width / 2;
  m_y = window_height / 2 - height / 2;
  m_width = width;
  m_height = height;

  m_renderer = renderer;
  m_texture = SDL_CreateTexture(renderer.get(), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, width, height);
  m_surface = SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0);
  m_pixels = (Uint32 *)m_surface->pixels;

  for (int i = 0; i < width; i++) {
    for (int j = 0; j < height; j++) {
      m_pixels[j * m_surface->w + i] = (0xFF << 24) | (0xFF << 16) | (0xFF << 8) | 0xFF;
    }
  }
  SDL_UpdateTexture(m_texture, NULL, m_surface->pixels, m_surface->w * sizeof(Uint32));
}
PixelWorld::~PixelWorld() {
  SDL_FreeSurface(m_surface);
  SDL_DestroyTexture(m_texture);
}

void PixelWorld::point(int x, int y, Uint8 r, Uint8 g, Uint8 b) {
  m_pixels[x * m_surface->h + y] = (r << 24) | (g << 16) | (b << 8) | 0xFF;
}
void PixelWorld::update_position(int xrel, int yrel) {
  m_x += xrel;
  m_y += yrel;
}

void PixelWorld::zoom_in(int mousex, int mousey) {
  if (m_scale > 1000000) return;

  m_scale *= (1 + zoom_scale);
  m_x -= zoom_scale * (mousex - m_x);
  m_y -= zoom_scale * (mousey - m_y);
}
void PixelWorld::zoom_out(int mousex, int mousey) {
  if (m_scale < 0.05) return;

  m_scale /= (1 + zoom_scale);
  m_x += (zoom_scale / (1 + zoom_scale)) * (mousex - m_x);
  m_y += (zoom_scale / (1 + zoom_scale)) * (mousey - m_y);
}

void PixelWorld::render() {
  SDL_UpdateTexture(m_texture, NULL, m_surface->pixels, m_surface->w * sizeof(Uint32));
  SDL_Rect r = {m_x, m_y, (int)(m_width * m_scale), (int)(m_height * m_scale)};
  SDL_RenderCopy(m_renderer.get(), m_texture, NULL, &r);
}