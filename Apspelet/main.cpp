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

#include <string>   //Bra text strängar
#include <vector>   //Vector smarata listor
#include <sstream>  //Gör int till sträng


#define Wheigt 600 //fönstrets storlek
#define Wwidth 800

using namespace std;


/*

 Förkunskap:
 
 I denhär rendreringsmotorn SDL så är uppåt minus och
 neråt plus.
 
*/


class Sprites // En liten hjälp klass med statiska funktioner 
{             // Dvs funktioner alla kan nå via :: operatorn
    
public:
    
    static SDL_Texture * Load_texture(string path,SDL_Renderer * rend) // Laddar textur
    {
        SDL_Surface * temp = IMG_Load(path.c_str());
        
        SDL_Texture * tex = SDL_CreateTextureFromSurface(rend, temp);
        
        SDL_FreeSurface(temp); // ta bort temporär data
        
        
        return tex;
    }
    
    static bool check_collision( SDL_Rect A, SDL_Rect B ) // kollar efter kolisioner
    {                                                     // kod lånad från stack owerflow
        //The sides of the rectangles                         (Orkade inte skriva egen)
        int leftA, leftB;
        int rightA, rightB;
        int topA, topB;
        int bottomA, bottomB;
        
        //Calculate the sides of rect A
        leftA = A.x;
        rightA = A.x + A.w;
        topA = A.y;
        bottomA = A.y + A.h;
        
        //Calculate the sides of rect B
        leftB = B.x;
        rightB = B.x + B.w;
        topB = B.y;
        bottomB = B.y + B.h;
        
        //If any of the sides from A are outside of B
        if( bottomA <= topB )
        {
            return false;
        }
        
        if( topA >= bottomB )
        {
            return false;
        }
        
        if( rightA <= leftB )
        {
            return false;
        }
        
        if( leftA >= rightB )
        {
            return false;
        }
        
        //If none of the sides from A are outside B
        return true;
    }
    
    static void render_text(TTF_Font * font, SDL_Renderer * rend,const char * text ,SDL_Rect * pos) // skriver en text
    {
        SDL_Color black={0,0,0};
        
        SDL_Surface * temp = TTF_RenderText_Blended(font, text ,black);
        
        SDL_Texture * tex = SDL_CreateTextureFromSurface(rend, temp);
        
        pos->w = temp->w;
        pos->h = temp->h;
    
        SDL_FreeSurface(temp);
        
        SDL_RenderCopy(rend, tex, NULL, pos);

        SDL_DestroyTexture(tex);
    }
    
};









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

    
    srand(time(0));
    
    
    game Game;
    Game.init(renderer);
    //kör igång spelet
    
    SDL_Event event;

    bool play = true;
                                          
    while (play) {
        
        SDL_RenderClear(renderer); //töm buffer

        Game.loop(); //lopp
        
        while(SDL_PollEvent(&event)) { //event
            // Skickar vidare events
            // till underligande kod
        
            if (event.type == SDL_QUIT || event.key.keysym.sym == SDLK_ESCAPE) {
                play = false;
                break;
            }
            
            Game.even(&event);
            
            
        }
        
        Game.render(renderer); //render

        
        SDL_RenderPresent(renderer); //buffer -> Skärm
        
        SDL_Delay(10); //Vänta lite så att inte du tar all cpu

    }
    
    Game.cleanup();
    
    //stäng ner spelet
    IMG_Quit();
    TTF_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(screen);

}
