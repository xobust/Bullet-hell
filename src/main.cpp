//
//  main.m
//  Apspelet
//
/*
    
    Ett litet spel med en appa som hoppar på moln och plockar
    Bannaner.
 
    
    Libs som krävs SDL2, SDL_ttf2, SDL_img2
 
*/
//
//  Created by Alexander Bladh on 2013-10-02.
//  Copyright (c) 2013 ab. All rights reserved.
//

#include <SDL2/SDL.h>               //Graafik, event.. osv
#include <SDL2_ttf/SDL_ttf.h>       //Typsnit, text
#include <SDL2_image/SDL_image.h>   //Ladda bilder i olika format
#include <SDL2/SDL_opengl.h>

#include <string>   //Bra text strängar
#include <vector>   //Vector smarata listor
#include <sstream>  //Gör int till sträng


#define Wheigt 600 //fönstrets storlek
#define Wwidth 800

using namespace std;


#include "game.h"
#include "backend/timer.h"

/*

 Förkunskap:
 
 I denhär rendreringsmotorn SDL så är uppåt minus och
 neråt plus.
 
*/


int main(int argc, char *argv[])
{
 
    SDL_Window *screen;
    SDL_Renderer *renderer;
    
    screen = SDL_CreateWindow("Dat monkey game",
                                   SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,Wwidth, Wheigt, 0);
    renderer = SDL_CreateRenderer(screen, -1, SDL_RENDERER_ACCELERATED);
    // gör en skärm
    
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
    
    
    IMG_Init(IMG_INIT_PNG);
    TTF_Init();
    //startar bibliotek

    
    srand((unsigned)time(0));
    
    
    Game game;
    game.init(renderer);
    //kör igång spelet
    
    SDL_Event event;
    bool play = true;
    
    Timer fps;
                                          
    while (play) {
        
        fps.start();
        
        SDL_RenderClear(renderer); //töm buffer

        game.loop(); //lopp
        
        while(SDL_PollEvent(&event)) { //event
            // Skickar vidare events
            // till underligande kod
        
            if (event.type == SDL_QUIT || event.key.keysym.sym == SDLK_ESCAPE) {
                play = false;
                break;
            }
            
            game.even(&event);
            
            
        }
        
        game.render(renderer); //render

        
        SDL_RenderPresent(renderer); //buffer -> Skärm
        
        if(( fps.get_ticks() < 1000 / 120 ) )
        {
            SDL_Delay( ( 1000 / 120) - fps.get_ticks()); // Max 60 bildrutor per secund
        }

    }
    
    game.cleanup();
    
    //stäng ner spelet
    IMG_Quit();
    TTF_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(screen);
    
    
    return EXIT_SUCCESS;
}
