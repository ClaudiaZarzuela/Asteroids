// This file is part of the course TPV2@UCM - Samir Genaim

#include "Texture.h"

Texture& Texture::operator=(Texture &&other) noexcept {
	this->~Texture();
	texture_ = other.texture_;
	other.texture_ = nullptr;
	renderer_ = other.renderer_;
	other.renderer_ = nullptr;
	width_ = other.width_;
	height_ = other.height_;

	return *this;
}

Texture::Texture(Texture &&other) noexcept {
	texture_ = other.texture_;
	other.texture_ = nullptr;
	renderer_ = other.renderer_;
	other.renderer_ = nullptr;
	width_ = other.width_;
	height_ = other.height_;
}

Texture::Texture(SDL_Renderer *renderer, const std::string &fileName) {
	assert(renderer != nullptr);

	SDL_Surface *surface = IMG_Load(fileName.c_str());
	if (surface == nullptr)
		throw "Couldn't load image: " + fileName;

	texture_ = SDL_CreateTextureFromSurface(renderer, surface);
	if (texture_ == nullptr) {
		SDL_FreeSurface(surface);
		throw "Couldn't convert surface to texture for image: " + fileName;
	}

	width_ = surface->w;
	height_ = surface->h;
	renderer_ = renderer;

	SDL_FreeSurface(surface);
}

Texture::Texture(SDL_Renderer *renderer, const std::string &text,
		const Font &font, const SDL_Color &fgColor) {
	constructFromText(renderer, text, font, &fgColor);
}

Texture::Texture(SDL_Renderer *renderer, const std::string &text,
		const Font &font, const SDL_Color &fgColor, const SDL_Color &bgColor) {
	constructFromText(renderer, text, font, &fgColor, &bgColor);
}

Texture::Texture(SDL_Renderer* renderer, const std::string& fileName, int rows, int cols) {
	assert(renderer != nullptr);

	SDL_Surface* surface = IMG_Load(fileName.c_str());
	if (surface == nullptr)
		throw "Couldn't load image: " + fileName;

	texture_ = SDL_CreateTextureFromSurface(renderer, surface);
	if (texture_ == nullptr) {
		SDL_FreeSurface(surface);
		throw "Couldn't convert surface to texture for image: " + fileName;
	}

	width_ = surface->w;
	height_ = surface->h;
	renderer_ = renderer;
	numCols_ = cols;
	numRows_ = rows;

	SDL_FreeSurface(surface);
}

void Texture::renderFrame(const SDL_Rect& destRect, int row, int col, int angle, SDL_RendererFlip flip) const {
	SDL_Rect srcRect;
	srcRect.x = width_ * col;
	srcRect.y = height_ * row;
	srcRect.w = width_;
	srcRect.h = height_;
	SDL_RenderCopyEx(renderer_, texture_, &srcRect, &destRect, angle, 0, flip);
}
void Texture::constructFromText(SDL_Renderer *renderer, const std::string &text,
		const Font &font, const SDL_Color *fgColor, const SDL_Color *bgColor) {
	assert(renderer != nullptr);

	SDL_Surface *textSurface =
			bgColor == nullptr ?
					font.renderText(text, *fgColor) :
					font.renderText(text, *fgColor, *bgColor);

	if (textSurface == nullptr)
		throw "Couldn't create surface for text: " + text;

	texture_ = SDL_CreateTextureFromSurface(renderer, textSurface);
	if (texture_ == nullptr) {
		SDL_FreeSurface(textSurface);
		throw "Couldn't create texture for text: " + text;
	}

	width_ = textSurface->w;
	height_ = textSurface->h;
	renderer_ = renderer;

	SDL_FreeSurface(textSurface);
}
