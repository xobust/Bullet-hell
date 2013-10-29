
//
//  level.cpp
//  Apspelet
//
//  Created by Alexander Bladh on 2013-10-26.
//  Copyright (c) 2013 ab. All rights reserved.
//

#include "level.h"

#include <fstream>
#include <sstream>


using namespace std;

void Level::load(SDL_Renderer * rend, string mapfile)
{
    
    cloud_tex = Sprites::Load_texture("moln.png", rend);
    rCloud_tex = Sprites::Load_texture("moln red.png", rend);
    bullet_tex = Sprites::Load_texture("bullet.png", rend);
    
    
    std::string   line =
    "Begin 10 2 100 0 5 5"
    "N 70 2 700 0 5 5"
    "N 120 2 100 0 5 5"
    "N 130 3 200 0 2 50"
    "N 140 3 550 0 2 50"
    "N 140 100 550 0 5 4"
    "N 190 100 550 0 5 4";

    std::stringstream   ss(line);
    
    while(ss.good())
    {
        std::string         str;
        ss << str;
        Command c;
        ss >> c.Name;
        ss >> c.time;
        ss >> c.type;
        ss >> c.x;
        ss >> c.y;
        ss >> c.repeat;
        ss >> c.delay;
        
        commands.push_back(c);
    }
    
    fire = false;
    level_time.start();
}

void Level::render(SDL_Renderer * renderer)
{
    
    for (vector<Bullet*>::iterator it = bullets.begin(); it != bullets.end(); it++) {
        
        //renderar alla kulor på respektive plateser
        
        (*it)->render(renderer);
        
        
    }
    
    for (vector<Enemy*>::iterator it = enemies.begin(); it != enemies.end(); it++) {
        
        //renderar alla fienden på respektive plateser
        (*it)->render(renderer);
        
    }
    
}

void Level::event(SDL_Event * event)
{
    
    switch(event->type)
    {
        case SDL_KEYDOWN:
            
            switch(event->key.keysym.sym){
                case SDLK_z:
                    fire = true;
                    fire_timer.start();
                break;
                    

            }
            break;
        case SDL_KEYUP:
            switch (event->key.keysym.sym) {
                case SDLK_z:
                    fire = false;
                    break;
                    
                default:
                    break;
            }
            
            break;
    }
}

void Level::exec_command(Command c)
{
    
    SDL_Rect r;
    r.x = c.x;
    r.y = c.y;
    
    switch (c.type)
    {
        case 1:
        {
    
            break;
        }
        case 2:
        {
            r.w = 40;
            r.h = 40;
            Cloud * cloud = new Cloud(cloud_tex, r);
            enemies.push_back(cloud);

            break;
        }
        case 3:
        {
            r.w = 50;
            r.h = 50;
            Cloud_F * cloud = new Cloud_F(rCloud_tex, r);
            enemies.push_back(cloud);
            
            break;
        }
        case 100:
        {
            for (vector<Enemy*>::iterator it = enemies.begin(); it != enemies.end(); it++)
            {
                if ((*it)->type == 3) {
                    for (int i=0; i<180; i+= 4) {
                        fireball * f = new fireball(bullet_tex, (*it)->pos, 3, i);
                        bullets.push_back(f);
                    }
                }
            }

            
            break;
        }
    }
}

void Level::loop(player * Player)
{
    
    for (vector<Command>::iterator it = commands.begin(); it != commands.end();)
    {
        if(level_time.get_ticks() > it->time*100)
        {
            exec_command(*it);
            it->repeat--;
            if (it->repeat <= 0) {
                it = commands.erase(it);
            }else
            {
                it->time += it->delay;
            }
            
        }else
        {
            it++;
        }
    }
    
    for (vector<Bullet*>::iterator it = bullets.begin(); it != bullets.end();) {
        
        (*it)->loop();
        
        if((*it)->type != 1 && Sprites::check_collision((*it)->col, Player->Col_Rect))
        {
            Player->die();
        }
        
        if((*it)->dead())
        {
            delete (*it);
            it = bullets.erase(it);
        }else
            it++;
        
    }
    
    for (vector<Enemy*>::iterator it = enemies.begin(); it != enemies.end();)
    {
        
        (*it)->loop();
        
        if(Sprites::check_collision((*it)->col, Player->Col_Rect))
        {
            Player->die();
        }
        
        for (vector<Bullet*>::iterator ib = bullets.begin(); ib != bullets.end();)
        {
            if ((*ib)->type == 1) {
            
            if(Sprites::check_collision((*it)->col, (*ib)->col))
            {
                (*ib)->helth--;
                (*it)->helth--;
            }
                
            }
                
            if ((*ib)->dead()) {
                delete (*ib);
                ib = bullets.erase(ib);
            }else
            {
                ib++;
            }
            
        }
        
        
        if((*it)->dead())
        {
            delete (*it);
            it = enemies.erase(it);
        }else
            it++;
        
    }
    
    if(fire && fire_timer.get_ticks() > 100)
    {
        banana * b = new banana(Player->bullet_tex, Player->Col_Rect,1);
        
        bullets.push_back(b);
        
        fire_timer.start();
    }
    
}
