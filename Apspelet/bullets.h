//
//  bullets.h
//  Apspelet
//
//  Created by Alexander Bladh on 2013-10-21.
//  Copyright (c) 2013 ab. All rights reserved.
//

#ifndef Apspelet_bullets_h
#define Apspelet_bullets_h


struct Bullet        //moln struktur
{
protected:
    SDL_Texture * texture;
    float rotation;
    
public:
    int helth;
    
    SDL_Rect pos;
    SDL_Rect col;
    
    Bullet(SDL_Texture * tex, SDL_Rect position, int t):texture(tex),pos(position)
    {
        
    }
    
    
    void render(SDL_Renderer * renderer)
    {
        SDL_RenderCopyEx(renderer, texture,NULL, &pos, rotation,NULL,SDL_FLIP_NONE);
    }
    
    virtual void loop(double delta_time)
    {
        
        col.x=pos.x;
        col.y=pos.y;
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
