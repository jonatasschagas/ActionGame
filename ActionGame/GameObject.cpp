//
//  GameObject.cpp
//  SDLTest
//
//  Created by Jonatas Chagas on 26/10/2013.
//  Copyright (c) 2013 Jonatas Chagas. All rights reserved.
//

#include "GameObject.h"
#include "RenderingUtils.h"


GameObject::GameObject()
{
    //Initialize the offsets
    x = 0;
    y = 0;
    prevX = 0;
    prevY = 0;
    
    //Initialize the velocity
    xVel = 0;
    yVel = 0;
    isMoving = false;
}

void GameObject::init(SDL_Surface* screen,SDL_Rect* camera,TileMap* tileMap)
{
	this->screen = screen;
	this->camera = camera;
	this->tileMap = tileMap;
}

Animation* GameObject::getAnimation(int action)
{
    for(vector<Animation*>::iterator it = listAnimations.begin(); it != listAnimations.end(); ++it) {
        Animation* obj = *it;
        if(obj && obj->action == action)
        {
            return obj;
        }
    }
    return NULL;
}

bool GameObject::isCameraFocused()
{
    return cameraFocused;
}

int GameObject::getX()
{
    return x;
}

int GameObject::getY()
{
    return y;
}

int GameObject::getW()
{
    return w;
}

int GameObject::getH()
{
    return h;
}

void GameObject::handleInput(SDL_Event* event)
{
    if( event->type == SDL_KEYDOWN )
    {
        isMoving = true;
        switch( event->key.keysym.sym )
        {
            case SDLK_UP:
                yVel -= h / MOVING_SPEED;
                direction = UP;
                currentAction = ACTION_UP;
                break;
            case SDLK_DOWN:
                yVel += h / MOVING_SPEED;
                direction = DOWN;
                currentAction = ACTION_DOWN;
                break;
            case SDLK_LEFT:
                xVel -= w / MOVING_SPEED;
                direction = LEFT;
                currentAction = ACTION_LEFT;
                break;
            case SDLK_RIGHT:
                xVel += w / MOVING_SPEED;
                direction = RIGHT;
                currentAction = ACTION_RIGHT;
                break;
            case SDLK_SPACE:
                currentAction = direction + ACTION_SHOOT;
                break;
        }
    }
    else if(event->type == SDL_KEYUP)
    {
        isMoving = false;
        xVel = 0;
        yVel = 0;
    }
}

void GameObject::move(vector<GameObject*> list)
{

    prevX = x;
    prevY = y;
    
    x += xVel;
    
    if( ( x < 0 ) || ( x + w > LEVEL_WIDTH ) )
    {
        //move back
        x -= xVel;
    }
    
    //Move the dot up or down
    y += yVel;
    
    //If the dot went too far up or down
    if( ( y < 0 ) || ( y + h > LEVEL_HEIGHT ) )
    {
        //move back
        y -= yVel;
    }
    
    // tests the collision against other objects in the screen
    for(vector<GameObject*>::iterator it = list.begin(); it != list.end(); ++it) {
        GameObject* obj = *it;
        if(obj && obj != this)
        {
            int result = SDL_CollideBoundingBox(this->x , this->y, this->w, this->h,
                                                obj->getX() , obj->getY(),obj->getW(), obj->getH());
            
            if(result != 0)
            {
                // collided...
				// lets reset the values
                x = prevX;
                y = prevY;
                return;
            }
        }
    }
    
}

/**
 Returns to the previous position
 **/
void GameObject::moveBack()
{
    x = prevX;
    y = prevY;
}

void GameObject::show()
{
    
    // here we will show the animation depending on the
    // action of the input
    Animation* animation = getAnimation(currentAction);
    
    if(animation)
    {
        if(animation->currentFrame >= animation->numberOfFrames || isMoving == false)
        {
            animation->currentFrame = 0;
        }
        else
        {
            animation->currentFrame++;
        }
        
		// if this is true we focus the camera
        // on the game object
        if(cameraFocused)
        {
            if(animation->numberOfFrames > 0)
            {
                SDL_Rect* cameraGameObject = RenderingUtils::get_rect(x - camera->x, y - camera->y);
                RenderingUtils::apply_surface( animation->image,animation->listClips[animation->currentFrame],
                                              screen,cameraGameObject);
            }
            else
            {
                RenderingUtils::apply_surface(animation->image,NULL,screen,RenderingUtils::get_rect(x,y));
            }
        }
        else
        {
            if(animation->numberOfFrames > 0)
            {
                RenderingUtils::apply_surface(animation->image,animation->listClips[animation->currentFrame],screen,RenderingUtils::get_rect(x,y));
            }
            else
            {
                RenderingUtils::apply_surface(animation->image,NULL , screen,RenderingUtils::get_rect(x,y));
            }
        }
        
    }
}

void GameObject::setCamera()
{
    
    //Center the camera over the game object
    camera->x = ( x + this->w / 2 ) - SCREEN_WIDTH / 2;
    camera->y = ( y + this->h / 2 ) - SCREEN_HEIGHT / 2;
    
    //Keep the camera in bounds.
    if( camera->x < 0 )
    {
        camera->x = 0;
    }
    if( camera->y < 0 )
    {
        camera->y = 0;
    }
    if( camera->x > LEVEL_WIDTH - camera->w )
    {
        camera->x = LEVEL_WIDTH - camera->w;
    }
    if( camera->y > LEVEL_HEIGHT - camera->h )
    {
        camera->y = LEVEL_HEIGHT - camera->h;
    }
}
