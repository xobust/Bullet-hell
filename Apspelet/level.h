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


struct command
{
    int time;
    string command;
    
}


class level
{
    
    std::vector<Enemy> enemies; 
    std::vector<Bullet> bullets;
    
    std::vector<command> commands;
    
    int last_command_time;
    
public:
    
    void load(string filename)
    {
        
        
    }
    
    void render(SDL_Renderer * renderer)
    {
        
        SDL_RenderCopy(renderer, Bg, NULL, NULL);
        
        for (vector<Bullet>::iterator it = bullets.begin(); it != bullets.end(); it++) {
            
            //renderar alla kulor på respektive plateser
            
            it->render(renderer);
            
            
        }
        
        for (vector<Enemy>::iterator it = enemies.begin(); it != enemies.end(); it++) {
            
            //renderar alla fienden på respektive plateser
            it->render(renderer);
            
        }
        
        Player.render(renderer);
        
        if (Player.dead()) { // om du är död via medelande
            SDL_Rect r = {Wwidth/2,Wheigt/2,200,50};
            Sprites::render_text(font, renderer, "You are dead" , &r);
        }
        
        
        SDL_Rect r = {Wwidth-100,Wheigt-100,20,40};
        
        std::string s;
        std::stringstream out;
        out << points;
        s = out.str();
        
        Sprites::render_text(font, renderer, s.c_str() , &r);
        
    }

    void exec_command(command c)
    {
        
    }
    
    void loop()
    {
        for (vector<command>::iterator it = commands.begin(); it != commands.end();)
        {
            
            if(last_command_time > it->time)
            {
                exec_command(*it);
                commands.erase(it);
            }
        }
        
        for (vector<Bullet>::iterator it = bullets.begin(); it != bullets.end();) {
            
            it->loop(deltaTime);
            
            if(it->type != 1 && Sprites::check_collision(it->col, Player.Col_Rect))
            {
                Player.die();
            }
            
            if(it->outside())
            {
                it = bullets.erase(it);
            }else
                it++;
            
        }
        
        for (vector<Enemy>::iterator it = enemies.begin(); it != enemies.end();)
        {
            
            it->loop(deltaTime);
            
            for (vector<Bullet>::iterator ib = bullets.begin(); ib != bullets.end();)
            {
                if(Sprites::check_collision(it->col, ib->col))
                {
                    ib->helth--;
                    it->helth--;
                }
                
                if (ib->helth <= 0) {
                    ib = bullets.erase(ib);
                }else
                {
                    ib++;
                }
                
            }
            
            
            if(it->outside()||it->helth <= 0)
            {
                it = enemies.erase(it);
            }else
                it++;
            
        }
        
    }
    
    
    
    
}


#endif
