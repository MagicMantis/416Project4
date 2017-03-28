#ifndef OBJECTMANAGER_H
#define OBJECTMANAGER_H

#include <SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <map>
#include "texture.h"

/**
 * TextureManager class: this class loads and manages references to
 * all textures neccessary for the game. It also manages the memory
 * and frees used textures upon deconstruction.
 */
class TextureManager {
public:
	TextureManager() : textures() {}
	~TextureManager();

	Texture* getTexture(const std::string&) const; //request reference to texture 
	SDL_Texture* getBackgroundTexture() const; //request reference to background
	void initTextures(SDL_Renderer*); //load all textures from files
private:
	std::map<std::string, Texture*> textures; //map allow named access to texture pointers
	SDL_Texture* background; //background texture reference

	//internal functions
	SDL_Texture* loadTexture(SDL_Renderer*, const std::string&); //used to load a texture from a file
};

#endif
