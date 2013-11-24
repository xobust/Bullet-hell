//
//  Objects.h
//  Apspelet
//
//  Created by Alexander Bladh on 20131105.
//  Copyright (c) 2013 ab. All rights reserved.
//

#ifndef Apspelet_Objects_h
#define Apspelet_Objects_h

#include <cmath>
#include <SDL2/SDL.h>

#include "Timer.h"
#include "Sprites.h"

/*
 
 Circle colision base class
 
 */

class Circle
{
    
    SDL_Rect * rect;
    
protected:
    
    float x;
    float y;
    
    float w;
    float h;
    
    int radius;

    
public:
    
    Circle()
    {
        rect = new SDL_Rect();
    }
    
    
    SDL_Rect * Rect()
    {
        rect->x = x;
        rect->y = y;
        rect->w = w;
        rect->h = h;
        
        return rect;
    }
    
    SDL_Rect ColRect() const 
    {
        SDL_Rect r;
        
        r.x = x+(w/2)-radius;
        r.y = y+(h/2)-radius;
        r.w = radius * 2;
        r.h = radius * 2;
        
        return r;
    }
    
    
    
    /*
     Checks for colission with another circel 
     */
    bool colide(const Circle * Shape) const
    {
        
        float dx = (Shape->x + Shape->w/2 ) - (x+w/2);
        float dy = (Shape->y + Shape->h/2) - (y+h/2);
        float drad = Shape->radius + radius;
        
        if ( (dx * dx) + (dy * dy) < (drad * drad) )
        {
            return true;
        }
        else
        {
            return false;
        }
        
    }
      
    
};


/*
 
 Base class for all renderd sprites
 
 */

class Rendering_Object: public Circle
{
    
protected:
    
    Timer time;
    
    SDL_Texture * texture;
    
public:
    
    
    int type; // type    1 = enemy, 2 = bullet, 10 = player
    int subtype;  
    
    
    Rendering_Object(SDL_Texture * tex, int t):type(t),texture(tex)
    {
        time.start();
    }
    
    ~Rendering_Object()
    {
        
    }

    virtual void loop(int time) = 0;
    virtual void render(SDL_Renderer * renderer) = 0;
    
    
    virtual void HandleColisions( Rendering_Object * rend)
    {
        
    }
    
    virtual bool dead()=0;
    
    bool CheckColisions( Rendering_Object * Obj) const
    {
        //if (Sprites::BoxCollision(Circle::ColRect(), Obj->Circle::ColRect()))
            return Circle::colide(Obj);
        //else
        //    return false;
    };
    
};


#endif
