//
//  Objects.h
//  Apspelet
//
//  Created by Alexander Bladh on 2013-11-05.
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
    
    //Distance between two given points in a cordinate systen
    float euclideanDistance(float x, float y,float xb,float yb)
    {
        
        return sqrt( pow(xb-x,2) + pow(yb-y,2) );
    }
    
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
    
    SDL_Rect ColRect()
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
    bool colide(const Circle * Shape)
    {
        
        return ( euclideanDistance(x+w/2, y+h/2, Shape->x+Shape->w/2 ,Shape->y+Shape->h/2)
                <= (radius + Shape->radius) );
        
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
        SDL_DestroyTexture(texture);
    }

    virtual void loop() = 0;
    virtual void render(SDL_Renderer * renderer) = 0;
    
    
    virtual void HandleColisions( Rendering_Object * rend)
    {
        
    }
    
    virtual bool dead()=0;
    
    
    bool CheckColisions( Rendering_Object * Obj)
    {
        return Circle::colide(Obj);
    };
    
};


#endif
