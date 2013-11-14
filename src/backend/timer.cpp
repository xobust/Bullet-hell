//
//  timer.cpp
//  Apspelet
//
//  Created by Alexander Bladh on 2013-10-26.
//  Copyright (c) 2013 ab. All rights reserved.
//

#include "timer.h"
#include <SDL2/sdl.h>

Timer::Timer()
{
    startTicks = 0;
    pausedTicks = 0;
    
    paused = false;
    started = false;
}

void Timer::start()
{
    started = true;
    paused = false;
    
    startTicks = SDL_GetTicks();
    
}

void Timer::stop()
{
    //Stop the timer
    started = false;
    //Unpause the timer
    paused = false;
}


int Timer::get_ticks(int t)
{
    //If the timer is running
    if( paused == true )
    { //Return the number of ticks when the timer was paused
        return pausedTicks;
    } else {
        //Return the current time minus the start time
        return t - startTicks;
    }
    //If the timer isn't running
    return 0;
}

int Timer::get_ticks()
{
    return get_ticks(SDL_GetTicks());
}



double Timer::seconds()
{
    return get_ticks()/1000.0f;
}

void Timer::pause()
{
    //If the timer is running and isn't already paused
    if( ( started == true ) && ( paused == false ) )
    { //Pause the timer
        paused = true;
        //Calculate the paused ticks
        pausedTicks = SDL_GetTicks() - startTicks;
    }
}

void Timer::unpause()
{
    //If the timer is paused
    if( paused == true )
    {
        //Unpause the timer
        paused = false;
        //Reset the starting ticks
        startTicks = SDL_GetTicks() - pausedTicks;
        //Reset the paused ticks
        pausedTicks = 0;
    }
}

bool Timer::is_paused() { return paused; }

bool Timer::is_started() {return started;}

int Timer::pause_time()
{
    return SDL_GetTicks() - (pausedTicks + startTicks);
}