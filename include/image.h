/*! An abstraction for loaded and created images.
 *
 * This class encapsulates the required functionality for creating and using
 * images that are either created within or externally loaded from the local
 * filesystem. In summary, this class encapsulates SDL_Texture management.
 */
#ifndef SPACE_INVADERS_IMAGE_H
#define SPACE_INVADERS_IMAGE_H

#include <memory>
#include <string>

// forward declarations in the global namespace.
struct SDL_Texture;
struct SDL_Renderer;
struct SDL_Color;
struct _TTF_Font;

namespace space_invaders
{
  class Image final
  {
  public:
    Image(SDL_Texture* texture);
    ~Image();

    static std::shared_ptr<Image> fromFile(SDL_Renderer* renderer, const std::string& filename);
    static std::shared_ptr<Image> fromText(SDL_Renderer* renderer, const std::string& text, SDL_Color& color, _TTF_Font* font);

          SDL_Texture* getTexture()       { return mTexture; }
    const SDL_Texture* getTexture() const { return mTexture; }

    int getWidth()  const { return mWidth;  }
    int getHeight() const { return mHeight; }
  private:
    SDL_Texture*  mTexture;
    int           mWidth;
    int           mHeight;
  };
  typedef std::shared_ptr<Image> ImagePtr;
}

#endif