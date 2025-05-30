/*****************************************************************************
 Yihsiang Liow
 Copyright
 *****************************************************************************/
#ifndef COLOR_H
#define COLOR_H

#include <iostream>
#include "SDL.h"

#ifdef SDL_Color
typedef SDL_Color Color;
#else
typedef SDL_Colour Color;
#endif

/*
class Color
{
	int r, g, b;
};
*/

const Color BLACK    = {  0,   0,   0, 0};
const Color RED      = {255,   0,   0, 0};
const Color WHITE    = {255, 255, 255, 0};
const Color GREEN    = {  0, 255,   0, 0};
const Color BLUE     = {  0,   0, 255, 0};
const Color GRAY     = {130, 130, 130, 0};
const Color DARKGRAY = { 50,  50,  50, 0};
const Color YELLOW   = {231, 228,  13, 0};
const Color CYAN     = {  0, 255, 255, 0};
const Color ORANGE   = {255, 114,   0, 0};


inline Color rand_color()
{
    Color c = {Uint8(rand() % 256), Uint8(rand() % 256), Uint8(rand() % 256), 0};
    return c;
}

#endif 
