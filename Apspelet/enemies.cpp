//
//  enemies.cpp
//  Apspelet
//
//  Created by Alexander Bladh on 2013-10-24.
//  Copyright (c) 2013 ab. All rights reserved.
//

#include "enemies.h"


void Enemy::loop()
{
    col.y = (int) y;
    col.x = (int) x;
}


void Cloud::loop()
{
    y = (time.seconds() * 100) + my;
    
    col.y = (int) y;
    col.x = (int) x;
}


void Cloud_F::loop()
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
    }
    
    
    y = (time.seconds() * 100) + my;

    
    col.y = (int) y;
    col.x = (int) x;
}
