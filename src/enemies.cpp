//
//  enemies.cpp
//  Apspelet
//
//  Created by Alexander Bladh on 2013-10-24.
//  Copyright (c) 2013 ab. All rights reserved.
//

#include "enemies.h"


void Enemy::loop(int ticks)
{

}


void Cloud::loop(int ticks)
{
    y = (time.seconds() * 100) + my;
    
}


void Cloud_F::loop(int ticks)
{
    if(time.seconds()>1 && stage == 0)
    {
        if (!time.is_paused()) {
            time.pause();
        }
    }
    
    if(time.pause_time() > 5000 && time.is_paused())
    {
        stage++;
        time.unpause();
        active = false;
    }
    
    
    y = (time.seconds() * 100) + my;
}

void Cloud_S::loop(int ticks)
{
    x=time.seconds()*100;
    y = (-0.0025f)*x*x+2*x;
}

void Boss::loop(int ticks)
{
    y=100;
    x=350;
}