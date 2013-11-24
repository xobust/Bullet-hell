//
//  Texture_Manager.h
//  Apspelet
//
//  Created by Alexander Bladh on 2013-11-05.
//  Copyright (c) 2013 ab. All rights reserved.
//

#ifndef Apspelet_Resource_Manager_h
#define Apspelet_Resource_Manager_h

#include "singletondestroyer.h"

#include <string>
#include <SDL2/SDL.h>
#include <atomic>
#include <mutex>
#include <unordered_map>


class ResourceManager
{
    
public:
    
    static ResourceManager * getInstance();
    
    virtual ~ResourceManager();
    
    SDL_Texture * loadTexture(std::string name, SDL_Renderer* rend);
    
    
private:
    
    ResourceManager();
    ResourceManager(const ResourceManager & ref);
    const ResourceManager& operator=(const ResourceManager& ref);
    
    static ResourceManager* mpInstance;
    static SingletonDestroyer<ResourceManager> mDestroyer;
    
    std::unordered_map<std::string, SDL_Texture*> mTextureMap;
    
};
    

#endif
