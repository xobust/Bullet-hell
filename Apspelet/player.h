//
//  player.h
//  Apspelet
//
//  Created by Alexander Bladh on 2013-10-21.
//  Copyright (c) 2013 ab. All rights reserved.
//

#ifndef Apspelet_player_h
#define Apspelet_player_h

class player
{
    
    SDL_Texture * P_Texture; //Spelarns textur
    SDL_Texture * Col_texture;
    
    double mx; // Förflyttning i x
    double my; // och y led   (per 100 ms)
    
    int jump_time;   //Tiden då ett hopp började
    
    
    SDL_Rect P_pos; //spelar position
    
    int hp;
    int power;
    int points;
    
    bool focus;
    
    
public:
    
    SDL_Rect Col_Rect;  //colisions rectangel mot moln
    
    
    bool Load(SDL_Renderer * renderer)
    {
        /*
         Regel nummer 1 i c++
         Sätt alltid dina värde innan du börjar
         
         */
        
        P_Texture = Sprites::Load_texture("apa.png", renderer);
        Col_texture = Sprites::Load_texture("col.png", renderer);
        
        
        jump_time = 0;
        
        P_pos.x = Wwidth/2 + P_pos.w/2;
        P_pos.y = Wheigt*0.9f;
        P_pos.w = 80;
        P_pos.h = 120;
        
        Col_Rect = P_pos;
        Col_Rect.h = 20;
        Col_Rect.y -= 110;
        
        hp = 5;
        
        focus = false;
        
        mx = 0;
        my = 0;
        
        return true;
    }
    
    void event(SDL_Event * event) //event hantering
    {
        switch(event->type)
        {
            case SDL_KEYDOWN:
                if(jump_time==0)
                    jump_time = SDL_GetTicks();
                
                switch(event->key.keysym.sym){
                    case SDLK_LEFT:
                        mx = -20;
                        break;
                    case SDLK_RIGHT:
                        mx = 20;
                        break;
                    case SDLK_UP:
                        my = -20;
                        break;
                    case SDLK_DOWN:
                        my = 20;
                        break;
                        
                    case SDLK_LSHIFT:
                        focus = true;
                        break;
                }
                break;
                
                
            case SDL_KEYUP:
                switch(event->key.keysym.sym){
                    case SDLK_LEFT:
                        if(mx < 0)
                            mx=0;
                        break;
                    case SDLK_RIGHT:
                        if(mx>0)
                            mx = 0;
                        break;
                    case SDLK_UP:
                        if(my<0)
                            my = 0;
                        
                        break;
                    case SDLK_DOWN:
                        if(my>0)
                            my = 0;
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
            if(mx > 0)
                mx = 7;
            else if (mx < 0)
                mx = -7;
            
            if(my > 0)
                my = 7;
            else if (my < 0)
                my = -7;
        }
        
        P_pos.x += (double)(mx * deltaTime); // förflyttning gånger antalet 100ms som gått
        P_pos.y += (double)(my * deltaTime);
        
        
        if (P_pos.y > Wheigt) {
            P_pos.y = Wheigt;
        }else if(P_pos.y < 0)
        {
            P_pos.y = 0;
        }
        
        if(P_pos.x > Wwidth)
        {
            P_pos.x = Wwidth;
        }else if (P_pos.x < 0)
        {
            P_pos.x = 0;
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
    
    void loop(double delta_time)
    {
        
        move(delta_time);
        
        Col_Rect = P_pos;
        Col_Rect.h = 20;
        Col_Rect.w = 20;
        Col_Rect.x += (P_pos.w/2) - 10;
        Col_Rect.y += P_pos.h/2;
        
    }
    
    void render(SDL_Renderer * renderer)
    {
        
        
        SDL_RenderCopy(renderer, P_Texture, NULL, &P_pos); //visar spelaren
        
        if(focus)
            SDL_RenderCopy(renderer, Col_texture, NULL, &Col_Rect);
        
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
