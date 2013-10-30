//
//  Grant.h
//  SDLTest
//
//  Created by Jonatas Chagas on 26/10/2013.
//  Copyright (c) 2013 Jonatas Chagas. All rights reserved.
//

#ifndef __SDLTest__Grant__
#define __SDLTest__Grant__

#include "GameObject.h"
#include <iostream>

const string GRANT_UP = "grant_up.png";
const string GRANT_DOWN = "grant_down.png";
const string GRANT_LEFT = "grant_left.png";
const string GRANT_RIGHT = "grant_right.png";
const string GRANT_RIGHT_SHOOT = "grant_right_shoot.png";
const string GRANT_UP_SHOOT = "grant_up_shoot.png";
const string GRANT_LEFT_SHOOT = "grant_left_shoot.png";
const string GRANT_DOWN_SHOOT = "grant_down_shoot.png";

class Grant: public GameObject
{
public:
    Grant();
};


#endif /* defined(__SDLTest__Grant__) */
