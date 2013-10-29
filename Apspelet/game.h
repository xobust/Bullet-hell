//
//  game.h
//  Apspelet
//
//  Created by Alexander Bladh on 2013-10-21.
//  Copyright (c) 2013 ab. All rights reserved.
//

#ifndef Apspelet_game_h
#define Apspelet_game_h

#include "Sprites.h"
#include "player.h"
#include "level.h"


class game
{
    player Player;
    Level test_level;
    
    SDL_Texture * Bg;
    
    TTF_Font * font; //font
    
    double deltaTime;
    int thisTime;
    int lastTime;
    
    int points; // poäng
    
public:
    
    
    
    bool init(SDL_Renderer * renderer)
    {
        Bg = Sprites::Load_texture("bg.png", renderer);
        
        font = TTF_OpenFont("OpenSans-Regular.ttf", 23);
        
        
        SDL_Rect r;
        r.x = 100;
        r.y = 0;
        r.w = 50;
        r.h = 50;
        
        test_level.load(renderer, "test.lvl");
        
        
        Player.Load(renderer);
        
        deltaTime = 0.0;
        thisTime = 0;
        lastTime = 0;
        
        points = 0;
        
        return true;
    }
 

    
    void even(SDL_Event * event)
    {
        // Skickar vidare events
        // till underligande kod ( spelaren)
        
        Player.event(event);
        test_level.event(event);
        
        switch(event->type)
        {
            case SDL_KEYDOWN:
                switch (event->key.keysym.sym) {
                    case SDLK_x:
                        //add_bullets();
                        break;
                        
                    default:
                        break;
                }
                
                
                break;
                
        }
    }
    
    
    void render(SDL_Renderer * renderer)
    {
        
        SDL_RenderCopy(renderer, Bg, NULL, NULL);
        
        Player.render(renderer);
        
        test_level.render(renderer);
        
        
        if (Player.dead()) { // om du är död via medelande
            SDL_Rect r = {Wwidth/2,Wheigt/2,200,50};
            Sprites::render_text(font, renderer, "You are dead" , &r);
        }
        
        
        SDL_Rect r = {Wwidth-100,Wheigt-100,20,40};
        
        std::string s;
        std::stringstream out;
        out << points;
        s = out.str();
        
        Sprites::render_text(font, renderer, s.c_str() , &r);
        
    }
    
    void loop()
    {
        /*
         
         Update positions
         
         */
        thisTime = SDL_GetTicks();                      //tids skillnads uträkning
        deltaTime = (double)(thisTime - lastTime) / 100.0f;
        lastTime = thisTime;
         
        Player.loop();
        test_level.loop(&Player);
    }
    
    
    void cleanup()
    {
        
        //gör rent
        Player.cleanup();
        
        SDL_DestroyTexture(Bg);
        
        TTF_CloseFont(font);
        
    }
    
    
};


#endif
