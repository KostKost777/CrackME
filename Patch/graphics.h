#ifndef GRAPHICS
#define GRAPHICS

#include <SFML/Graphics.h>

const float WIDTH  = 2000;
const float HEIGHT = 1200;

const size_t BLUE_TABLET_X_CENTRE = 1411; 
const size_t BLUE_TABLET_Y_CENTRE = 631; 
const size_t BLUE_TABLET_RADIUS   = 80; 

const size_t RED_TABLET_X_CENTRE = 642; 
const size_t RED_TABLET_Y_CENTRE = 560; 
const size_t RED_TABLET_RADIUS   = 81;

enum TabletType
{
    BLUE,
    RED,
    UNKNOWN
};

void PlayMelody();

void SetFullScreenBackgroundScale(sfSprite* background_sprite, sfTexture* background_texture, 
                                  size_t width, size_t height);

sfText* CreateTextObject(const char* message, sfFont* font, sfColor color, int x, int y);

size_t CalcPointsDistance(size_t x_1, size_t y_1, size_t x_2, size_t y_2);

TabletType ShowUserInterface();

TabletType ParsePressButton(size_t x_coord, size_t y_coord);

#endif