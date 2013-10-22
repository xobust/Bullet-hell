//
//  enemies.h
//  Apspelet
//
//  Created by Alexander Bladh on 2013-10-21.
//  Copyright (c) 2013 ab. All rights reserved.
//

#ifndef Apspelet_enemies_h
#define Apspelet_enemies_h

class Enemy
{
    int type;
    SDL_Texture * texture;
    
public:
    
    int helth;
    
    SDL_Rect pos;
    SDL_Rect col;
    
    
    
    Enemy(SDL_Texture * tex, int t, SDL_Rect rec)
    {
        texture = tex;
        type = t;
        pos = rec;
        helth = 1;
        
    }
    
    virtual void loop(double delta_time)
    {
        pos.y += (15.0f * delta_time);
        col=pos;
    }
    
    
    void render(SDL_Renderer * renderer)
    {
        SDL_RenderCopy(renderer, texture, NULL, &pos);
    }
    
    
    bool outside()
    {
        if(pos.y > Wheigt )
        {
            return true;
        }else if(pos.y < 0)
        {
            return true;
        }else if(pos.x > Wwidth)
        {
            return true;
        }else if (pos.x < 0)
        {
            return true;
        }
        
        return false;
        
        /*Spaggeti version
         
         return ((pos.y > Wheigt )||(pos.y < 0)(pos.x > Wwidth)||(pos.x < 0))
         */
    }
    
    
};


#endif
