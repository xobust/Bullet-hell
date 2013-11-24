//
//  game.cpp
//  Apspelet
//
//  Created by Alexander Bladh on 2013-10-30.
//  Copyright (c) 2013 ab. All rights reserved.
//

#include "backend/globals.h"
#include "backend/Resource_Manager.h"

#include "game.h"

#include <sstream>

using namespace std;

bool Game::init(SDL_Renderer * renderer)
{
    Bg = ResourceManager::getInstance()->loadTexture("bg.png", renderer);
    
    font = TTF_OpenFont("OpenSans-Regular.ttf", 23);
    
    
    SDL_Rect r;
    r.x = 100;
    r.y = 0;
    r.w = 50;
    r.h = 50;
    
    test_level.load(renderer, "test.lvl");
    
    return true;
}



void Game::even(SDL_Event * event)
{
    // Skickar vidare events
    // till underligande kod ( spelaren)
    
    test_level.event(event);
    
    switch(event->type)
    {
        case SDL_KEYDOWN:
            switch (event->key.keysym.sym) {
                case SDLK_x:
                    //add_bullets();
                    break;
                    
                default:
                    break;
            }
            
            
            break;
            
    }
}


void Game::render(SDL_Renderer * renderer)
{
    
    SDL_RenderCopy(renderer, Bg, NULL, NULL);
    
    test_level.render(renderer);
    
    

    SDL_Rect box;
    box.w = 175;
    box.h = 600;
    box.x=625;
    box.y=0;
    SDL_RenderFillRect(renderer,&box);
    
    
    
}

void Game::loop()
{
    /*
     
     Update positions
     
     */

    test_level.loop();
}


void Game::cleanup()
{
    
    SDL_DestroyTexture(Bg);
    
    TTF_CloseFont(font);
    
}
