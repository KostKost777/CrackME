#ifndef GRAPHICS
#define GRAPHICS

const float WIDTH  = 2000;
const float HEIGHT = 1200;

const size_t BLUE_TABLET_X_CENTRE = 1411; 
const size_t BLUE_TABLET_Y_CENTRE = 631; 
const size_t BLUE_TABLET_RADIUS   = 80; 

const size_t RED_TABLET_X_CENTRE = 642; 
const size_t RED_TABLET_Y_CENTRE = 560; 
const size_t RED_TABLET_RADIUS   = 81; 

size_t CalcPointsDistance(size_t x_1, size_t y_1, size_t x_2, size_t y_2);

void PrintPicture();

void ParsePressButton(size_t x_coord, size_t y_coord);

#endif