//
//  game.h
//  Apspelet
//
//  Created by Alexander Bladh on 2013-10-21.
//  Copyright (c) 2013 ab. All rights reserved.
//

#ifndef Apspelet_game_h
#define Apspelet_game_h


class game
{
    player Player;
    
    SDL_Texture * Bg;
    SDL_Texture * Cloud_texture;
    SDL_Texture * Banana_texture;
    
    std::vector<Enemy> enemies;
    std::vector<Bullet> bullets;
    
    
    TTF_Font * font; //font
    
    double deltaTime;
    int thisTime;
    int lastTime;
    
    int points; // poäng
    
public:
    
    
    
    bool init(SDL_Renderer * renderer)
    {
        Bg = Sprites::Load_texture("bg.png", renderer);
        
        Cloud_texture = Sprites::Load_texture("moln.png", renderer);
        
        Banana_texture = Sprites::Load_texture("Bannan.png", renderer);
        
        font = TTF_OpenFont("OpenSans-Regular.ttf", 23);
        
        
        SDL_Rect r;
        r.x = 100;
        r.y = 0;
        r.w = 50;
        r.h = 50;
        
        Enemy e(Cloud_texture,1,r);
        
        enemies.push_back(e);
        
        
        Player.Load(renderer);
        
        deltaTime = 0.0;
        thisTime = 0;
        lastTime = 0;
        
        bullets.clear();
        
        
        
        points = 0;
        
        
        return true;
    }
    
    void add_bullets()
    {
        Bullet  b(Banana_texture,Player.Col_Rect,1);
        
        bullets.push_back(b);
        
        
    }
    
    
    void even(SDL_Event * event)
    {
        // Skickar vidare events
        // till underligande kod ( spelaren)
        
        Player.event(event);
        
        switch(event->type)
        {
            case SDL_KEYDOWN:
                switch (event->key.keysym.sym) {
                    case SDLK_x:
                        add_bullets();
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
        
        for (vector<Bullet>::iterator it = bullets.begin(); it != bullets.end(); it++) {
            
            //renderar alla kulor på respektive plateser
            
            it->render(renderer);
            
            
        }
        
        for (vector<Enemy>::iterator it = enemies.begin(); it != enemies.end(); it++) {
            
            //renderar alla fienden på respektive plateser
            it->render(renderer);
            
        }
        
        Player.render(renderer);
        
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
        
        
        
        Player.loop(deltaTime);
        
        
        for (vector<Bullet>::iterator it = bullets.begin(); it != bullets.end();) {
            
            it->loop(deltaTime);
            
            if(it->type != 1 && Sprites::check_collision(it->col, Player.Col_Rect))
            {
                Player.die();
            }
            
            if(it->outside())
            {
                it = bullets.erase(it);
            }else
                it++;
            
        }
        
        for (vector<Enemy>::iterator it = enemies.begin(); it != enemies.end();)
        {
            
            it->loop(deltaTime);
            
            for (vector<Bullet>::iterator ib = bullets.begin(); ib != bullets.end();)
            {
                if(Sprites::check_collision(it->col, ib->col))
                {
                    ib->helth--;
                    it->helth--;
                }
                
                if (ib->helth <= 0) {
                    ib = bullets.erase(ib);
                }else
                {
                    ib++;
                }
                
            }
            
            
            if(it->outside()||it->helth <= 0)
            {
                it = enemies.erase(it);
            }else
                it++;
            
        }
        
    }
    
    
    void cleanup()
    {
        
        //gör rent
        Player.cleanup();
        
        SDL_DestroyTexture(Bg);
        SDL_DestroyTexture(Cloud_texture);
        SDL_DestroyTexture(Banana_texture);
        
        TTF_CloseFont(font);
        
    }
    
    
};


#endif
