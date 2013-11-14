//
//  Sprites.h
//  Apspelet
//
//  Created by Alexander Bladh on 2013-10-22.
//  Copyright (c) 2013 ab. All rights reserved.
//

#ifndef Apspelet_Sprites_h
#define Apspelet_Sprites_h

#include <string>
#include <SDL2_ttf/SDL_ttf.h>
#include <SDL2_image/SDL_image.h>


class Sprites // En liten hjälp klass med statiska funktioner
{             // Dvs funktioner alla kan nå via :: operatorn
    
public:
    
    static SDL_Texture * Load_texture(std::string path,SDL_Renderer * rend) // Laddar textur
    {
        SDL_Surface * temp = IMG_Load(path.c_str());
        
        SDL_Texture * tex = SDL_CreateTextureFromSurface(rend, temp);
        
        SDL_FreeSurface(temp); // ta bort temporär data
        
        
        return tex;
    }
    
    
    
    // Fill circle by gpwiki.org
    /*
     * SDL_Surface 32-bit circle-fill algorithm without using trig
     *
     * While I humbly call this "Celdecea's Method", odds are that the
     * procedure has already been documented somewhere long ago.  All of
     * the circle-fill examples I came across utilized trig functions or
     * scanning neighbor pixels.  This algorithm identifies the width of
     * a semi-circle at each pixel height and draws a scan-line covering
     * that width.
     *
     * The code is not optimized but very fast, owing to the fact that it
     * alters pixels in the provided surface directly rather than through
     * function calls.
     *
     * WARNING:  This function does not lock surfaces before altering, so
     * use SDL_LockSurface in any release situation.
     */
    
    static void fill_circle(SDL_Surface *surface, int cx, int cy, int radius, Uint32 pixel)
    {
        // Note that there is more to altering the bitrate of this
        // method than just changing this value.  See how pixels are
        // altered at the following web page for tips:
        //   http://www.libsdl.org/intro.en/usingvideo.html
        static const int BPP = 4;
        
        double r = (double)radius;
        
        for (double dy = 1; dy <= r; dy += 1.0)
        {
            // This loop is unrolled a bit, only iterating through half of the
            // height of the circle.  The result is used to draw a scan line and
            // its mirror image below it.
            
            // The following formula has been simplified from our original.  We
            // are using half of the width of the circle because we are provided
            // with a center and we need left/right coordinates.
            
            double dx = floor(sqrt((2.0 * r * dy) - (dy * dy)));
            int x = cx - dx;
            
            // Grab a pointer to the left-most pixel for each half of the circle
            Uint8 *target_pixel_a = (Uint8 *)surface->pixels + ((int)(cy + r - dy)) * surface->pitch + x * BPP;
            Uint8 *target_pixel_b = (Uint8 *)surface->pixels + ((int)(cy - r + dy)) * surface->pitch + x * BPP;
            
            for (; x <= cx + dx; x++)
            {
                *(Uint32 *)target_pixel_a = pixel;
                *(Uint32 *)target_pixel_b = pixel;
                target_pixel_a += BPP;
                target_pixel_b += BPP;
            }
        }
    }
    
    
    static bool BoxCollision(SDL_Rect A, SDL_Rect B)  // kollar efter kolisioner
    {                                                          // kod lånad från stack owerflow
        
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
            return false;
        else if( topA >= bottomB )
            return false;
        
        else if( rightA <= leftB )
            return false;
        
        else if( leftA >= rightB )
            return false;
    
        
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
        
        SDL_DestroyTexture(tex); //Dealocation verry slow :/
    }
    
};

#endif
