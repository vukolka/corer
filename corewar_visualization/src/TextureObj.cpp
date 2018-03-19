//
// Created by vukolov on 19.02.18.
//

#include <iostream>
#include "TextureObj.h"

void TextureObj::free()
{
	if (lTexture)
		SDL_DestroyTexture(lTexture);
	lTexture = nullptr;
}

bool TextureObj::loadTextureFromText(const char *text, SDL_Color textColor)
{
	free();
	SDL_Surface *text_surf = TTF_RenderText_Blended(lFont, text, textColor);
	if (!text_surf)
	{
		std::cout << "Can\'t initialize IMG with PNG flag, " << "SDL_Error :" << TTF_GetError() << std::endl;
		return (false);
	}
	lTexture = SDL_CreateTextureFromSurface(lRenderer, text_surf);
	if (!lTexture)
	{
		std::cout << "Can\'t creat Texture, " << "SDL_Error :" << SDL_GetError() << std::endl;
		return (false);
	}
	lWidth = text_surf->w;
	lHeight = text_surf->h;

	SDL_FreeSurface(text_surf);
	return true;
}

void TextureObj::initTexture(SDL_Renderer *pRenderer, TTF_Font *pFont)
{
	lRenderer = pRenderer;
	lFont = pFont;
}

void TextureObj::render(int x, int y, SDL_Rect *clip, double angle, SDL_Point *center, SDL_RendererFlip flip)
{
	SDL_Rect renderQuad = { x, y, lWidth, lHeight};
	SDL_RenderCopy(lRenderer, lTexture, clip, &renderQuad);
}

TextureObj::TextureObj()
{
	lTexture = NULL;
}

void TextureObj::newTextue(SDL_Renderer *pRenderer, const char *string)
{
	SDL_Surface *loadedSurface;

	loadedSurface = IMG_Load(string);
	if (!loadedSurface)
	{
		std::cout << "Unable to load image" << string
				  <<"! SDL Error: " << IMG_GetError() << std::endl;
	}
	lTexture = SDL_CreateTextureFromSurface(pRenderer, loadedSurface);
	lWidth = loadedSurface->w;
	lHeight = loadedSurface->h;
	SDL_FreeSurface(loadedSurface);
}

void TextureObj::setInitialColor()
{
	if (lTexture)
		SDL_SetTextureAlphaMod(lTexture, 180);
}
