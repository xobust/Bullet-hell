//
//  Resource_Manager.cpp
//  Apspelet
//
//  Created by Alexander Bladh on 2013-11-17.
//  Copyright (c) 2013 ab. All rights reserved.
//

#include "Resource_Manager.h"
#include <SDL2_image/SDL_image.h>


ResourceManager* ResourceManager::mpInstance = 0;
SingletonDestroyer<ResourceManager> ResourceManager::mDestroyer;

ResourceManager* ResourceManager::getInstance()
{
	if(!(ResourceManager*)mpInstance)
	{
		mpInstance = new ResourceManager();
		mDestroyer.setSingleton(mpInstance);
	}
	return mpInstance;
}

SDL_Texture* ResourceManager::loadTexture(std::string path, SDL_Renderer* rend)
{
	std::string key = path;
	
	if(mTextureMap.count(key) == 0)
	{
		SDL_Surface * temp = IMG_Load(path.c_str());
        
        SDL_Texture * tex = SDL_CreateTextureFromSurface(rend, temp);
        
        mTextureMap.emplace(key, tex);
        
        SDL_FreeSurface(temp); // ta bort temporär data
        
        
        return tex;
	}
	else
	{
		return mTextureMap[key];
	}
}

ResourceManager::ResourceManager()
{
}

ResourceManager::~ResourceManager()
{
}


