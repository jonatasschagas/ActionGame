//
//  RenderingUtils.h
//  SDLTest
//
//  Created by Jonatas Chagas on 26/10/2013.
//  Copyright (c) 2013 Jonatas Chagas. All rights reserved.
//

#ifndef SDLTest_RenderingUtils_h
#define SDLTest_RenderingUtils_h

#include "SDLMain.h"
#include <SDL/SDL.h>
#include <SDL_image/SDL_image.h>
#include "SDL_collide.h"
#include <string>
#include <CoreFoundation/CoreFoundation.h>

using namespace std;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int LEVEL_WIDTH = 1280;
const int LEVEL_HEIGHT = 1280;
const int SCREEN_BPP = 32;
const int FRAMES_PER_SECOND = 50;
const string BACKGROUND_IMG = "map.png";

// the highest the moving speed the slowest the object
// moves on the screen
const int MOVING_SPEED = 5;


struct ColorKeyRGB
{
    int r = 0;
    int g = 0;
    int b = 0;
};


class RenderingUtils
{
public:
    // http://sdl-collide.sourceforge.net
    
    static void fill_colorkey(SDL_Surface* screen)
    {
        SDL_FillRect(screen,&screen->clip_rect,SDL_MapRGB(screen->format,
                                                          0,0,0));
    }
    
    static Uint32 get_pixel32( SDL_Surface *surface, int x, int y )
    {
        //Convert the pixels to 32 bit
        Uint32 *pixels = (Uint32 *)surface->pixels;
        
        //Get the requested pixel
        return pixels[ ( y * surface->w ) + x ];
    }
    
    static SDL_Surface *load_image(string filename)
    {
        SDL_Surface* loadedImage = NULL;
        SDL_Surface* optimizedImage = NULL;
        
        //filename = getResourcePath() + filename;
        
        loadedImage = IMG_Load( filename.c_str() );
        
        if( loadedImage != NULL )
        {
            optimizedImage = SDL_DisplayFormat( loadedImage );
            SDL_FreeSurface( loadedImage );
            
            /*if( optimizedImage != NULL )
            {
                Uint32 colorkey = SDL_MapRGB( optimizedImage->format, 0,0,0 );
                SDL_SetColorKey( optimizedImage, SDL_SRCCOLORKEY, colorkey );
            }*/
        }
        else
        {
            return NULL;
        }
        
        return optimizedImage;
    }
    
    static SDL_Surface *load_image(string filename,int r, int g, int b)
    {
        SDL_Surface* loadedImage = NULL;
        SDL_Surface* optimizedImage = NULL;
        
        //filename = getResourcePath() + filename;
        
        loadedImage = IMG_Load( filename.c_str() );
        
        if( loadedImage != NULL )
        {
            optimizedImage = SDL_DisplayFormat( loadedImage );
            SDL_FreeSurface( loadedImage );
            
            if( optimizedImage != NULL )
            {
                Uint32 colorkey = SDL_MapRGB( optimizedImage->format, r,g,b );
                SDL_SetColorKey( optimizedImage, SDL_SRCCOLORKEY, colorkey );
            }
        }
        else
        {
            return NULL;
        }
        
        return optimizedImage;
    }
    
    static string getResourcePath()
    {
        CFURLRef url = CFBundleCopyResourcesDirectoryURL(CFBundleGetMainBundle());
        CFStringRef str = CFURLCopyFileSystemPath(url, kCFURLPOSIXPathStyle);
        
        char path[PATH_MAX];
        CFStringGetCString(str,path,PATH_MAX,kCFStringEncodingUTF8);
        CFRelease(str);
        CFRelease(url);
        return path;
    }
    
    static SDL_Rect* get_rect(int x, int y)
    {
        SDL_Rect* rect = new SDL_Rect;
        rect->x = x;
        rect->y = y;
        return rect;
    }
    
    static void apply_surface(SDL_Surface* source = NULL,SDL_Rect* clip = NULL , SDL_Surface* destination = NULL,SDL_Rect* offset = NULL)
    {
        SDL_BlitSurface( source, clip, destination, offset );
    }
    
    static void clean_up(SDL_Surface *image)
    {
        SDL_FreeSurface(image);
        SDL_Quit();
    }
    
    static bool init(SDL_Surface* screen)
    {
        if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
        {
            return false;
        }
        
        screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );
        
        if( screen == NULL )
        {
            return false;
        }
        
        SDL_WM_SetCaption( "Event test", NULL );
        
        //If everything initialized fine
        return true;
    }
    
    static bool update(SDL_Surface* screen)
    {
        if( SDL_Flip( screen ) == -1 )
        {
            return false;
        }
        return true;
    }

    
};

#endif
