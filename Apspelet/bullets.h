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

struct Bullet        //moln struktur
{
protected:
    SDL_Texture * texture;
    float rotation;
    
    int c_time;
    
    SDL_Rect pos;
    
    float x ,y;
    float mx, my;
    
public:
    int type;
    int helth;
    SDL_Rect col;
    
    Bullet(SDL_Texture * tex, SDL_Rect position, int t):texture(tex),pos(position), type(t)
    {
        c_time = SDL_GetTicks();
        helth = 1;
        rotation = 0;
        x= pos.x;
        y = pos.y;
        my=y;
        mx = x;
    }
    
    
    virtual void render(SDL_Renderer * renderer)
    {
        pos.x = (int) x;
        pos.y = (int) y;
        SDL_RenderCopyEx(renderer, texture,NULL, &pos, rotation,NULL,SDL_FLIP_NONE);
    }
    
    virtual void loop()
    {
        
        col.x= (int)x;
        col.y= (int)y;
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
        pos.w = 20;
        pos.h = 20;
        col = pos;
        
        col.h *= 0.9f;
        col.w *= 0.9f;
        
        rotation = angle;
        
    };
    
    void loop()
    {
        y = my + ((SDL_GetTicks() - c_time)/7) * cos(rotation);
        x = mx + ((SDL_GetTicks() - c_time)/7) * sin(rotation);

        
        col.x= (int) x;
        col.y= (int) y;
    }
    
    
};

class banana: public Bullet
{
public:
    
    banana(SDL_Texture * tex, SDL_Rect position, int t):Bullet(tex, position, t)
    {
        pos.w = 20;
        pos.h = 20;
        col = pos;
        
        rotation = rand()%180;
    
    };
    
    void loop()
    {
        y = my - (SDL_GetTicks() - c_time) / 3.2f;
        
        
        col.x= (int) x;
        col.y= (int) y;
    }
    
    
};


#endif
