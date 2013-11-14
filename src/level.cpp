
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

void Level::load(SDL_Renderer * rend, string mapfil, player * Player)
{
    
    cloud_tex = Sprites::Load_texture("moln.png", rend);
    rCloud_tex = Sprites::Load_texture("moln red.png", rend);
    bullet_tex = Sprites::Load_texture("bullet.png", rend);
    
    Objects.push_back(Player);
    
    
    /* Old stuf std::string   line =
    "Begin 10 2 100 0 5 5"
    "N 70 2 700 0 5 5"
    "N 120 2 100 0 5 5"
    "N 130 3 200 0 2 50"
    "N 130 3 550 0 2 50"
    "Cos(v) 140 100 550 0 5 4"
    "N 190 100 550 0 5 4"
    "N 250 3 200 0 1 0"
    "N 250 3 550 0 1 0"
    "v=t 260 101 550 0 60 1"
    "N 300 3 500 0 1 0"
    "N 300 3 350 0 1 0"
    "N 300 3 150 0 1 0"
    "sin(y) 330 102 550 0 40 1"
    "N 330 103 550 0 40 1"
    "N 335 101 550 0 60 1"
    "Boss 400 20 1 1 0 0"
    "Polarcordinates 420 104 1 1 99 3"
    "N 450 4 1 1 10 5"
    "N 470 105 1 1 50 1"
    "N 470 106 1 1 50 20"
    "N 475 107 1 1 50 30"
    "N 600 3 350 0 2 50"
    "N 600 100 550 0 5 4"
    "N 650 3 550 0 1 0"
    "N 650 101 550 0 60 1";
    */
    
    std::string line =
    "Begin 10 2 100 0 5 5"
    "N 70 2 700 0 5 5"
    "N 120 2 100 0 5 5"
    "N 130 3 200 0 2 50"
    "N 140 3 550 0 2 50"
    "N 140 100 550 0 5 4"
    "N 190 100 550 0 5 4";

    

    std::stringstream   ss(line);
    
    stage = "Begin";
    
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
    
    level_time.start();
}

void Level::exec_command(Command c, player * Player)
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
            Objects.push_back(cloud);
            
            break;
        }
        case 3:
        {
            r.w = 50;
            r.h = 50;
            Cloud_F * cloud = new Cloud_F(rCloud_tex, r);
            Objects.push_back(cloud);
            
            break;
        }
        case 100:
        {
            vector<Rendering_Object*> tempvec; // avoid apending to a vector while iterating
            
            for (vector<Rendering_Object*>::iterator it = Objects.begin(); it != Objects.end(); it++)
            {
                if ((*it)->type == 1 && (*it)->subtype == 3) {
                    for (int i=0; i<180; i+= 4) {
                        fireball * f = new fireball(bullet_tex, (*it)->ColRect(), 3, i);
                        tempvec.push_back(f);
                    }
                }
            }
            
            Objects.insert(Objects.begin(), tempvec.begin(), tempvec.end());
            
            
            break;
        }
    }
}



void Level::render(SDL_Renderer * renderer)
{
    
    for (vector<Rendering_Object*>::iterator it = Objects.begin(); it != Objects.end(); it++) {
        
        
        //renderar alla kulor på respektive plateser
        
        (*it)->render(renderer);
        
        
    }
    
}

void Level::event(SDL_Event * event)
{
    
    switch(event->type)
    {
        case SDL_KEYDOWN:
            
            switch(event->key.keysym.sym){
                    

            }
            break;
        case SDL_KEYUP:
            switch (event->key.keysym.sym) {
                    
            }
            
            break;
    }
}

void Level::loop(player * Player)
{
    
    for (vector<Command>::iterator it = commands.begin(); it != commands.end();)
    {
        if(level_time.get_ticks() > it->time*100)
        {
            exec_command(*it, Player);
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
    
    
    for (vector<Rendering_Object*>::iterator it = Objects.begin(); it != Objects.end();)
    {
        
        Rendering_Object * current_objeckt = *it;
        
        current_objeckt->loop();

       for (vector<Rendering_Object*>::iterator ib = Objects.begin(); ib != Objects.end(); ib++)
       {
           if (it==ib) {
               continue;
           }
         
          Rendering_Object* test = *ib;
           
           if(current_objeckt->CheckColisions(test))
           {
               current_objeckt->HandleColisions(test);
           }
    
       }
    
        
        if (current_objeckt->dead() && current_objeckt->type != 10) {
            it = Objects.erase(it);
        }else
        {
            it++;
        }
    }
    
    Player->shoot(&Objects);

}
