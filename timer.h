//
//  timer.h
//  Apspelet
//
//  Created by Alexander Bladh on 2013-10-26.
//  Copyright (c) 2013 ab. All rights reserved.
//

#ifndef Apspelet_timer_h
#define Apspelet_timer_h

class Timer
{
private:
    //The clock time when the timer started
    int startTicks;
    
    //The ticks stored when the timer was paused
    int pausedTicks;
    
    //The timer status
    bool paused;
    bool started;
    
public:
    //Initializes variables
    Timer();
    
    //The various clock actions
    void start();
    void stop();
    void pause();
    void unpause();
    
    //Gets the timer's time
    int get_ticks();
    
    //Checks the status of the timer
    bool is_started();
    bool is_paused();

};


#endif
