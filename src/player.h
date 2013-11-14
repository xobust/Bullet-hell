//
//  player.h
//  Apspelet
//
//  Created by Alexander Bladh on 2013-10-21.
//  Copyright (c) 2013 ab. All rights reserved.
//

#ifndef Apspelet_player_h
#define Apspelet_player_h

#include <vector>

#include "backend/Sprites.h"
#include "backend/timer.h"
#include "backend/globals.h"
#include "backend/Objects.h"

#include "bullets.h"


/*
 
 Player class controlls the players movement and actions
 it is a child class to Rendering object for simplicity
 
 Todo: make this a base class and creat child classes
        for difrent characters.
 
 */

class player:public Rendering_Object
{
    
    SDL_Texture * Col_texture;

    bool focus;
    bool fire;
    Timer fire_timer;
    
    float xVel; // movement in x axis 
    float yVel; // -||- y axis (/ 100 ms)
    
    Timer delta;
    Timer respawn_Time;

public:

    int hp;
    int power;
    int points;
    
    SDL_Texture * bullet_tex;
    
    
    player():Rendering_Object(NULL,10)
    {
        subtype = 1;
    }
    
    
    bool Load(SDL_Renderer * renderer)
    {
        /*
         Textures are not loaded in constructor right now witch is 
         abit dangerous
         
         */
        
        texture = Sprites::Load_texture("apa.png", renderer);
        Col_texture = Sprites::Load_texture("col.png", renderer);
        bullet_tex = Sprites::Load_texture("bannan.png", renderer);
        
        
        type = 10;
        
        x = 300;
        y = 400;
        w = 80;
        h = 120;
        
        radius = 10;
        
        hp = 5;
        points = 0;
        power = 100;
        
        focus = false;
        fire = false;
        
        xVel = 0;
        yVel = 0;
        

        return true;
    }
    
    void event(SDL_Event * event) //event hantering
    {
        switch(event->type)
        {
            case SDL_KEYDOWN:
                
                switch(event->key.keysym.sym){
                    case SDLK_LEFT:
                        xVel = -200;
                        break;
                    case SDLK_RIGHT:
                        xVel = 200;
                        break;
                    case SDLK_UP:
                        yVel = -200;
                        break;
                    case SDLK_DOWN:
                        yVel = 200;
                        break;
                        
                    case SDLK_LSHIFT:
                        focus = true;
                        break;
                        
                    case SDLK_z:
                        fire = true;
                        fire_timer.start();
                        break;
                }
                break;
                
                
            case SDL_KEYUP:
                switch(event->key.keysym.sym){
                    case SDLK_LEFT:
                        if(xVel < 0)
                            xVel=0;
                        break;
                    case SDLK_RIGHT:
                        if(xVel>0)
                            xVel = 0;
                        break;
                    case SDLK_UP:
                        if(yVel<0)
                            yVel = 0;
                        
                        break;
                    case SDLK_DOWN:
                        if(yVel>0)
                            yVel = 0;
                        break;
                        
                    case SDLK_LSHIFT:
                        
                        focus = false;
                        
                        break;
                        
                    case SDLK_z:
                        fire = false;
                        fire_timer.start();
                        break;
                        
                    default:
                        break;
                }
                
                
                break;     
        }
    }
    
    
    void HandleColisions(Rendering_Object * rend)
    {
        if (rend->type == 2 && rend->subtype != 10) {
            die();
        }else if(rend->type == 1)
        {
            die();
        }
    }
    
    void move(double deltaTime)
    {
        
        if (focus) {
            if(xVel > 0)
                xVel = 150;
            else if (xVel < 0)
                xVel = -150;
            
            if(yVel > 0)
                yVel = 150;
            else if (yVel < 0)
                yVel = -150;
        }
        
        x += (xVel * deltaTime); // förflyttning gånger antalet 1 s som gått
        y += (yVel * deltaTime);
  
        
        
        if (y > Wheigt-h/1.5f) {
            y = Wheigt-h/1.5f;
        }else if(y < 0)
        {
            y = 0;
        }
        
        if(x > Wwidth-(175+w/2))
        {
            x = Wwidth-(175+w);
        }else if (x < 0)
        {
            x = 0;
        }
        
    }
    
    bool dead() //kollar om man är död
    {
        return hp <= 0;
    }
    
    void die()
    {
        if (!respawn_Time.is_started()) {
            hp--;
            respawn_Time.start();
            SDL_SetTextureAlphaMod(texture, 150);

        }
    }
    
    void loop(int ticks)
    {

        move(delta.seconds());
        
        delta.start();
        
        if(respawn_Time.is_started() && respawn_Time.seconds(ticks) > 4)
        {
            respawn_Time.stop();
            SDL_SetTextureAlphaMod(texture, 255);
        }
    }
    
    void render(SDL_Renderer * renderer)
    {
        SDL_RenderCopy(renderer, texture, NULL, Rect()); //visar spelaren
        
        auto r= ColRect();
        if(focus)
        {
            
            SDL_RenderCopy(renderer, Col_texture, NULL, &r);
        }
        
        
        SDL_RenderDrawRect(renderer, &r);

    }
    
    void shoot(std::vector<Rendering_Object*>* level)
    {
        
        if(fire && fire_timer.get_ticks() > 100)
        {
            banana * b = new banana(bullet_tex, ColRect());
            
            level->push_back(b);
            
            fire_timer.start();
        }
        
    }
    
    void abilety(std::vector<Rendering_Object*> level);
    //todo: add special abilety
    
    void cleanup()
    {

        SDL_DestroyTexture(texture);
        SDL_DestroyTexture(Col_texture);
        SDL_DestroyTexture(bullet_tex);
        
    }
    
    
};


#endif
