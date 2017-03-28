#ifndef TEXTURE_H
#define TEXTURE_H

#include <iostream>

/**
 * Texture class: this is a wrapper to the SDL_Texture object that adds
 * functionality and easier memory management. 
 */ 
class Texture {
public:
	Texture(SDL_Texture* i, int w, int h) : img(i), width(w), height(h) {}
	~Texture() { SDL_DestroyTexture(img); } //frees texture memory upon deletion

	SDL_Texture* getImage() const { return img; }
	int getWidth() const { return width; } //get width of the texture
	int getHeight() const { return height; } //get height of the texture

private:
	SDL_Texture* img;
	int width, height;

	//explicitly disallow compiler generated constructors
	Texture();
	Texture(const Texture&);
	Texture& operator=(const Texture&);
};

#endif
