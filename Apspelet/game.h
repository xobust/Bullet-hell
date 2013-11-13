//
//  game.h
//  Apspelet
//
//  Created by Alexander Bladh on 2013-10-21.
//  Copyright (c) 2013 ab. All rights reserved.
//

#ifndef Apspelet_game_h
#define Apspelet_game_h

#include "Sprites.h"
#include "player.h"
#include "level.h"


class Game
{
    player Player;// todo: move this to level
    Level test_level;
    
    SDL_Texture * Bg;
    
    TTF_Font * font; //font
    

public:
    
    bool init(SDL_Renderer * renderer);
    
    void even(SDL_Event * event);
    
    void render(SDL_Renderer * renderer);
    
    void loop();
    
    void cleanup();
    
    
};


#endif
