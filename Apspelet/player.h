//
//  player.h
//  Apspelet
//
//  Created by Alexander Bladh on 2013-10-21.
//  Copyright (c) 2013 ab. All rights reserved.
//

#ifndef Apspelet_player_h
#define Apspelet_player_h

#include "Sprites.h"
#include "timer.h"

class player
{
    
    SDL_Texture * P_Texture; //Spelarns textur
    SDL_Texture * Col_texture;
    
    
    int hp;
    int power;
    int points;
    bool focus;
    
    float xVel; // Förflyttning i x
    float yVel; // och y led   (per 100 ms)
    
    float x;
    float y;
    
    Timer delta;


public:

    SDL_Texture * bullet_tex;
    SDL_Rect Col_Rect;  //colisions rectangel mot moln
    SDL_Rect P_pos; //spelar position
    
    
    bool Load(SDL_Renderer * renderer)
    {
        /*
         Regel nummer 1 i c++
         Sätt alltid dina värde innan du börjar
         
         */
        
        P_Texture = Sprites::Load_texture("apa.png", renderer);
        Col_texture = Sprites::Load_texture("col.png", renderer);
        bullet_tex = Sprites::Load_texture("bannan.png", renderer);
        
        P_pos.x = 300;
        P_pos.y = 400;
        P_pos.w = 80;
        P_pos.h = 120;
        
        Col_Rect = P_pos;
        Col_Rect.h = 16;
        Col_Rect.w = 16;
        
        hp = 5;
        
        focus = false;
        
        xVel = 0;
        yVel = 0;
        
        x = 300;
        y = 400;
        
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
                        
                    default:
                        break;
                }
                
                
                break;
                
                
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
  
        
        
        if (y > Wheigt) {
            y = Wheigt;
        }else if(y < 0)
        {
            y = 0;
        }
        
        if(x > Wwidth)
        {
            x = Wwidth;
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
        hp--;
    }
    
    void loop()
    {

        move(delta.seconds());
        
        P_pos.x = (int) x;
        P_pos.y = (int) y;
        Col_Rect.x = x + (P_pos.w/2) - 10;
        Col_Rect.y = y + P_pos.h/2;
        
        delta.start();
    }
    
    void render(SDL_Renderer * renderer)
    {
        SDL_RenderCopy(renderer, P_Texture, NULL, &P_pos); //visar spelaren
        
        if(focus)
        {
            SDL_Rect r = Col_Rect;
            r.w *= 1.2f;
            r.h *= 1.2f;
            SDL_RenderCopy(renderer, Col_texture, NULL, &r);
        }
    }
    
    void cleanup()
    {
        
        /*
         Regel nummer 2 i c++
         
         Ta alltid bort det du inte användet och
         städa när du är klar
         
         */
        
        SDL_DestroyTexture(P_Texture);
        
    }
    
    
};


#endif
