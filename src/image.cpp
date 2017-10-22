#include "image.h"

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

using namespace space_invaders;

Image::Image(SDL_Surface* surface, SDL_Texture* texture) : mSurface(surface), mTexture(texture), mWidth(0), mHeight(0)
{
  // query for the width and height of the provided image texture.
  SDL_QueryTexture(texture, nullptr, nullptr, &mWidth, &mHeight);
}

Image::~Image()
{
  SDL_FreeSurface(mSurface);
  SDL_DestroyTexture(mTexture);
}

ImagePtr Image::fromFile(SDL_Renderer* renderer, const std::string& filename)
{
  // load the image surface from an external file.
  auto surface = IMG_Load(filename.c_str());
  if (surface == nullptr) {
    std::cerr << "Unable to load " << filename << ": " << IMG_GetError() << std::endl;
    return nullptr;
  }

  // create a texture from the loaded surface.
  auto texture = SDL_CreateTextureFromSurface(renderer, surface);
  if (texture == nullptr) {
    std::cerr << "Unable to create texture from surface: " << SDL_GetError() << std::endl;
    return nullptr;
  }

  // construct and return a new wrapper image instance.
  return std::make_shared<Image>(surface, texture);
}

ImagePtr Image::fromText(SDL_Renderer* renderer, const std::string& text, SDL_Color& color, _TTF_Font* font)
{
  // create a surface which contains the desired text.
  auto surface = TTF_RenderText_Blended(font, text.c_str(), color);
  if (surface == nullptr) {
    std::cerr << "Unable to create a surface with a text: " << TTF_GetError() << std::endl;
    return nullptr;
  }

  // create a new texture from the text surface.
  auto texture = SDL_CreateTextureFromSurface(renderer, surface);
  if (texture == nullptr) {
    std::cerr << "Unable to create texture from a text surface: " << SDL_GetError() << std::endl;
    return nullptr;
  }

  // construct and return a new wrapper image instance.
  return std::make_shared<Image>(surface, texture);
}

ImagePtr Image::stream(SDL_Renderer* renderer, int pixelFormat, int width, int height) {
  // create a new texture from the provided parameters.
  auto texture = SDL_CreateTexture(renderer, pixelFormat, SDL_TEXTUREACCESS_STREAMING, width, height);
  if (texture == nullptr) {
    std::cerr << "Unable to create a new streaming texture: " << SDL_GetError() << std::endl;
    return nullptr;
  }

  // construct and return a new wrapper image instance.
  return std::make_shared<Image>(nullptr, texture);
}