//
//  bullets.h
//  Apspelet
//
//  Created by Alexander Bladh on 2013-10-21.
//  Copyright (c) 2013 ab. All rights reserved.
//

#ifndef Apspelet_bullets_h
#define Apspelet_bullets_h

#include <SDL2/SDL.h>
#include <math.h>

#include "backend/timer.h"
#include "backend/Objects.h"

struct Bullet : public Rendering_Object
{
protected:
    float rotation;
    float mx, my;
    
public:
    int helth;
    
    Bullet(SDL_Texture * tex, SDL_Rect position, int t): Rendering_Object(tex,2)
    {
        subtype = t;
        
        helth = 1;
        rotation = 0;
        x= position.x;
        y= position.y;
        w= position.w;
        h= position.h;
        radius = (h/2)*0.8f;
        
        my=y;
        mx=x;
    }
    
    
    virtual void render(SDL_Renderer * renderer)
    {

        SDL_RenderCopyEx(renderer, texture,NULL, Rect(), rotation,NULL,SDL_FLIP_NONE);
    }
    
    virtual void HandleColisions( Rendering_Object * rend)
    {
        
    }
    
    virtual void loop()
    {
        
    }
    
    virtual bool dead()
    {
        return outside() || helth <= 0;
    }
    
    bool outside()
    {
        if(y > 600 )
        {
            return true;
        }else if(y < 0)
        {
            return true;
        }else if(x > 800)
        {
            return true;
        }else if (x < 0)
        {
            return true;
        }
        
        return false;
        
        /*Spaggeti version
         
         return ((pos.y > Wheigt )||(pos.y < 0)(pos.x > Wwidth)||(pos.x < 0))
         */
    }
    
    
    
};


class fireball: public Bullet
{
    
public:
    fireball(SDL_Texture * tex, SDL_Rect position, int t, float angle):Bullet(tex, position, t)
    {
        w = 20;
        h = 20;
        
        rotation = angle;
        
    };
    
    void loop()
    {
        y = my + ((time.get_ticks())/7) * cos(rotation);
        x = mx + ((time.get_ticks())/7) * sin(rotation);
    }
    
    
};


class looper: public Bullet
{
    
    float size;
    
public:
    looper(SDL_Texture * tex, SDL_Rect position, int t, float S):Bullet(tex, position, t)
    {
        w = 20;
        h = 20;
        size = S;

        
        rotation = 0;
        
    };
    
    void loop()
    {
        y = my + ((time.get_ticks())/7);
        x = mx + sin(y/100) * size;
        

    }
    
    
};


class rose: public Bullet
{
    int size;
public:
    
    rose(SDL_Texture * tex, SDL_Rect position, int t, int s):Bullet(tex, position, t)
    {
        w = 20;
        h = 20;
        time.start();
        size = s;
        
        rotation = rand()%180;
    
    };
    
    void loop()
    {
        
        x = mx +cos(size*time.seconds()/3)*sin(time.seconds()/3)*150;
        y = my +cos(size*time.seconds()/3)*cos(time.seconds()/3)*150;
        
    }
    
    virtual bool dead()
    {
        return time.seconds()>10 || helth <= 0;
    }
    
    
    
};



class seek: public Bullet
{
    
public:
    seek(SDL_Texture * tex, SDL_Rect position, int t, SDL_Rect p):Bullet(tex, position, t)
    {
        rotation = atan2(p.x-x, p.y-y);
    };
    
    void loop()
    {
        y = my + ((time.get_ticks())/10) * cos(rotation);
        x = mx + ((time.get_ticks())/10) * sin(rotation);
        
    }
    
    
};

class side: public Bullet
{
public:
    
    side(SDL_Texture * tex, SDL_Rect position, int t):Bullet(tex, position, t)
    {
        w = 20;
        h = 20;
        
    };
    
    void loop()
    {
        
        x = time.seconds()*50;
        
    }
    
    
};


class length: public Bullet
{

public:
    
    length(SDL_Texture * tex, SDL_Rect position, int t):Bullet(tex, position, t)
    {
        w = 20;
        h = 20;
        time.start();
        
    };
    
    void loop()
    {
        
        y = time.seconds()*50;
        
    }
    
    
};


class banana: public Bullet
{
public:
    
    banana(SDL_Texture * tex, SDL_Rect position):Bullet(tex, position, 10)
    {
        w = 20;
        h = 20;
        radius = 18;
        
        rotation = rand()%180;
        
    };
    
    void HandleColisions( Rendering_Object * rend)
    {

    }
    
    void loop()
    {
        y = my - (time.get_ticks()) / 3.2f;
        rotation = time.get_ticks()%360;
        

    }
    
    
};


#endif
