#include "textureManager.h"

SDL_Texture* TextureManager::loadTexture(SDL_Renderer* rend, const std::string& filename) {
	try {
		SDL_Texture *texture = IMG_LoadTexture(rend, filename.c_str());
		if ( texture == NULL ) {
			throw std::string("Couldn't load ") + filename;
		}
		return texture;
	}
	catch( const std::string& msg ) { 
		std::cout << msg << std::endl; 
		std::terminate();
	}
}

void TextureManager::initTextures(SDL_Renderer* rend) {
	//load background
	background = loadTexture(rend, "images/bkgnd.png");

	//load other textures
	SDL_Texture *building1 = loadTexture(rend, "images/building1.png");
	SDL_Texture *building2 = loadTexture(rend, "images/building2.png");
	SDL_Texture *rooftop = loadTexture(rend, "images/rooftop.png");
	SDL_Texture *detective = loadTexture(rend, "images/detective.png");
	SDL_Texture *criminal = loadTexture(rend, "images/criminal.png");
	SDL_Texture *dtext = loadTexture(rend, "images/dtext.png");
	SDL_Texture *ctext = loadTexture(rend, "images/ctext.png");
	SDL_Texture *lightning = loadTexture(rend, "images/lightning.png");

	//setup map
	textures["building1"] = new Texture(building1, 300, 450);
	textures["building2"] = new Texture(building2, 300, 450);
	textures["rooftop"] = new Texture(rooftop, 640, 400);
	textures["detective"] = new Texture(detective, 32, 64);
	textures["criminal"] = new Texture(criminal, 128, 64);
	textures["dtext"] = new Texture(dtext, 640, 100);
	textures["ctext"] = new Texture(ctext, 640, 100);
	textures["lightning"] = new Texture(lightning, 300, 300);
}

Texture* TextureManager::getTexture(const std::string& texName) const {
	return textures.at(texName);
}

SDL_Texture* TextureManager::getBackgroundTexture() const {
	return background;
}

TextureManager::~TextureManager() {
	for (std::map<std::string,Texture*>::iterator it=textures.begin(); it!=textures.end(); ++it)
		delete it->second;

 	SDL_DestroyTexture(background);
}
