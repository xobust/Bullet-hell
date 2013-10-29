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

#include <string>
#include <vector>

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


class Level
{
    
    std::vector<Enemy*> enemies;
    std::vector<Bullet*> bullets;
    std::vector<Command> commands;
    
    SDL_Texture * cloud_tex;
    SDL_Texture * rCloud_tex;
    SDL_Texture * bullet_tex;
    
    Timer level_time;
    
    bool fire;
    Timer fire_timer;
    
public:
    
    void load(SDL_Renderer * rend, std::string mapfile);
    
    void render(SDL_Renderer * renderer);

    void event(SDL_Event * event);

    
    void exec_command(Command c);
    
    void loop(player * Player);

};


#endif
