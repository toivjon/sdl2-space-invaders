#include "image.h"

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

using namespace space_invaders;

Image::Image(SDL_Texture* texture) : mTexture(texture), mWidth(0), mHeight(0)
{
  // query for the width and height of the provided image texture.
  SDL_QueryTexture(texture, nullptr, nullptr, &mWidth, &mHeight);
}

Image::~Image()
{
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
  SDL_FreeSurface(surface);
  if (texture == nullptr) {
    std::cerr << "Unable to create texture from surface: " << SDL_GetError() << std::endl;
    return nullptr;
  }

  // construct and return a new wrapper image instance.
  return std::make_shared<Image>(texture);
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
  SDL_FreeSurface(surface);
  if (texture == nullptr) {
    std::cerr << "Unable to create texture from a text surface: " << SDL_GetError() << std::endl;
    return nullptr;
  }

  // construct and return a new wrapper image instance.
  return std::make_shared<Image>(texture);
}
