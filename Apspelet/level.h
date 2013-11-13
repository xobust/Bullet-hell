//
//  level.h
//  Apspelet
//
//  Created by Alexander Bladh on 2013-10-22.
//  Copyright (c) 2013 ab. All rights reserved.
//

#ifndef Apspelet_level_h
#define Apspelet_level_h


#include "bullets.h"
#include "enemies.h"
#include "player.h" 
#include "Objects.h"

#include <string>
#include <vector>

/*
 Commands tells when to do what on the level
 
 Todo: replace with better solution, maby lua
 
 */

struct Command
{
    int time;
    std::string Name;
    int type;
    int x;
    int y;
    
    int repeat;
    int delay;
};


/*
 
 Level stores all info about the level 
 
 */


class Level
{
    
    //Stores active objects
    std::vector<Rendering_Object*> Objects;
    std::vector<Command> commands;
    
    
    //Temp texture location
    SDL_Texture * cloud_tex;
    SDL_Texture * rCloud_tex;
    SDL_Texture * bullet_tex;
    
    Timer level_time;
    
public:
    
    std::string stage;
    
    void load(SDL_Renderer * rend, std::string mapfile, player * Player);
    
    void render(SDL_Renderer * renderer);

    void event(SDL_Event * event);

    //executes a command
    void exec_command(Command c, player * Player);
    
    void loop(player * Player);

};


#endif
