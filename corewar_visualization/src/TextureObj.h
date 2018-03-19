#ifndef COREWARVIS_TEXTUREOBJ_H
#define COREWARVIS_TEXTUREOBJ_H

#include <string>
#include "SDL2/SDL_image.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"

class TextureObj
{
public:
	int				lWidth;
	int 			lHeight;

	TextureObj();
	//bool			loadFromFile(std::string path);
	void 			initTexture(SDL_Renderer	*pRenderer, TTF_Font *pFont);

	bool			loadTextureFromText(const char *text, SDL_Color textColor);

	void 			render(int x, int y,
						   SDL_Rect* clip = NULL,
						   double angle = 0.0,
						   SDL_Point* center = NULL,
						   SDL_RendererFlip flip = SDL_FLIP_NONE);
	void 			free();

	void			newTextue(SDL_Renderer *pRenderer, const char string[18]);

	void 			setInitialColor();

private:
	SDL_Texture		*lTexture;

	SDL_Renderer	*lRenderer;

	TTF_Font		*lFont;
};


#endif //COREWARVIS_TEXTUREOBJ_H
