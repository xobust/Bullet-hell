//
//  Sprites.h
//  Apspelet
//
//  Created by Alexander Bladh on 2013-10-22.
//  Copyright (c) 2013 ab. All rights reserved.
//

#ifndef Apspelet_Sprites_h
#define Apspelet_Sprites_h


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

#endif
