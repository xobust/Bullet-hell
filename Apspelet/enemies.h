//
//  enemies.h
//  Apspelet
//
//  Created by Alexander Bladh on 2013-10-21.
//  Copyright (c) 2013 ab. All rights reserved.
//

#ifndef Apspelet_enemies_h
#define Apspelet_enemies_h

#include <SDL2/SDL.h>
#include "timer.h"

#define Wheigt 600 //fönstrets storlek
#define Wwidth 800

class Enemy
{
protected:
 
    SDL_Texture * texture;
    
    Timer time;
    
    float x ,y;
    float mx, my;
    
public:
    
       int type;
    int helth;
    
    SDL_Rect pos;
    SDL_Rect col;
    
    
    
    Enemy(SDL_Texture * tex, SDL_Rect rec)
    {
        texture = tex;
        type = 0;
        pos = rec;
        col = rec;
        
        mx = rec.x;
        my = rec.y;
        
        x = rec.x;
        y = rec.y;
        helth = 5;
        time.start();
        
    }
    
    virtual void loop();

    
    
    void render(SDL_Renderer * renderer)
    {
        pos.x = (int) x;
        pos.y = (int) y;
        SDL_RenderCopy(renderer, texture, NULL, &pos);
    }
    
    
    virtual bool dead()
    {

        return (outside()||helth <= 0);
    }
    
    
    bool outside()
    {
        if(y > Wheigt + pos.h)
        {
            return true;
        }else if(y < 0-pos.h)
        {
            return true;
        }else if(x > Wwidth + pos.w)
        {
            return true;
        }else if (x < 0-pos.w)
        {
            return true;
        }
        
        return false;
        
        /*Spaggeti version
         
         return ((y > Wheigt )||(y < 0)(x > Wwidth)||(x < 0))
         */
    }
    
    
};


class Cloud:public Enemy
{

public:
    Cloud(SDL_Texture * tex, SDL_Rect rec):Enemy(tex, rec)
    {
        type = 1;
        helth = 3;
        time.start();
        
    }
    
    void loop();
    
};

class Cloud_F:public Enemy
{
    int stage;
    
public:
    Cloud_F(SDL_Texture * tex, SDL_Rect rec):Enemy(tex, rec)
    {
        type = 3;
        helth = 10;
        time.start();
        stage = 0;
    }
    
    void loop();
    
};

#endif
