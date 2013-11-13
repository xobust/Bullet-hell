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

#include "globals.h"
#include "Objects.h"
#include "bullets.h"

class Enemy : public Rendering_Object
{
protected:
    
    float mx, my;
    
public:
    
    int helth;
    bool active;
    
    
    Enemy(SDL_Texture * tex, SDL_Rect rec):Rendering_Object(tex,1)
    {
        subtype = 0;
        mx = rec.x;
        my = rec.y;
        
        x = rec.x;
        y = rec.y;
        w = rec.w;
        h = rec.h;
        radius = (h/2)*0.9;
        
        helth = 5;
        time.start();
        
    }
    
    virtual void loop();

    void render(SDL_Renderer * renderer)
    {
        SDL_RenderCopy(renderer, texture, NULL, Rect());
    }
    
    virtual void HandleColisions( Rendering_Object * rend)
    {
        if(rend->type == 2 && rend->subtype == 10)
        {
            helth--;
            Bullet * b = static_cast<Bullet*>(rend);
            
            b->helth--;
        }
        
        
    }
    
    virtual bool dead()
    {
        return (outside()||helth <= 0);
    }
    
    
    bool outside()
    {
        if(y > Wheigt + h)
        {
            return true;
        }else if(y < 0-h)
        {
            return true;
        }else if(x > Wwidth + w)
        {
            return true;
        }else if (x < 0-w)
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
        subtype = 1;
        helth = 3;
        time.start();
        active = false;
    }
    
    void loop();
    
};

class Cloud_F:public Enemy
{
    int stage;
    
public:
    Cloud_F(SDL_Texture * tex, SDL_Rect rec):Enemy(tex, rec)
    {
        subtype = 3;
        helth = 10;
        time.start();
        stage = 0;
        active = true;
    }
    
    void loop();
    
};


class Cloud_S:public Enemy
{
    int stage;
    
public:
    Cloud_S(SDL_Texture * tex, SDL_Rect rec):Enemy(tex, rec)
    {
        subtype = 4;
        helth = 10;
        time.start();
        stage = 0;
        active = true;
    }
    
    void loop();
    
};

class Boss:public Enemy
{
    int stage;
    
public:
    Boss(SDL_Texture * tex, SDL_Rect rec):Enemy(tex, rec)
    {
        subtype = 20;
        helth = 40;
        time.start();
        stage = 0;
        active = true;
    }
    
    void loop();
    
};

#endif
