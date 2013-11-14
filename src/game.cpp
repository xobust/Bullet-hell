//
//  game.cpp
//  Apspelet
//
//  Created by Alexander Bladh on 2013-10-30.
//  Copyright (c) 2013 ab. All rights reserved.
//

#include "backend/globals.h"
#include "game.h"

#include <sstream>

using namespace std;

bool Game::init(SDL_Renderer * renderer)
{
    Bg = Sprites::Load_texture("bg.png", renderer);
    
    font = TTF_OpenFont("OpenSans-Regular.ttf", 23);
    
    
    SDL_Rect r;
    r.x = 100;
    r.y = 0;
    r.w = 50;
    r.h = 50;
    
    test_level.load(renderer, "test.lvl", &Player);
    
    
    Player.Load(renderer);
    
    return true;
}



void Game::even(SDL_Event * event)
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


void Game::render(SDL_Renderer * renderer)
{
    
    SDL_RenderCopy(renderer, Bg, NULL, NULL);
    
    Player.render(renderer);
    
    test_level.render(renderer);
    
    
    if (Player.dead()) { // om du är död via medelande
        SDL_Rect r = {Wwidth/2,Wheigt/2,200,50};
        Sprites::render_text(font, renderer, "You are dead" , &r);
    }
    
    SDL_Rect box;
    box.w = 175;
    box.h = 600;
    box.x=625;
    box.y=0;
    SDL_RenderFillRect(renderer,&box);
    
    
    SDL_Rect r = {Wwidth-150,Wheigt-200,20,40};
    
    
    string s;
    stringstream out;
    out <<"Points: "<<Player.points;
    s = out.str();
    
    // SDL ttf fonts are to slow therfore disabeld atm
    //Sprites::render_text(font, renderer, s.c_str() , &r);
    
    out.str(std::string()); // empty the strig stream
    out <<"HP: "<<Player.hp;
    s = out.str();
    r.y -= 20;
    
    //Sprites::render_text(font, renderer, s.c_str() , &r);
    
    out.str(std::string());
    out <<"Power: "<< Player.power;
    s = out.str();
    r.y -= 20;
    
    //Sprites::render_text(font, renderer, s.c_str() , &r);
    
    out.str(std::string());
    out << test_level.stage;
    s = out.str();
    r.y -= 50;
    
    //Sprites::render_text(font, renderer, s.c_str() , &r);
    
    
}

void Game::loop()
{
    /*
     
     Update positions
     
     */

    Player.loop();
    test_level.loop(&Player);
}


void Game::cleanup()
{
    
    //gör rent
    Player.cleanup();
    
    SDL_DestroyTexture(Bg);
    
    TTF_CloseFont(font);
    
}
