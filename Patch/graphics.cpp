#include <stdio.h>
#include <math.h>
#include <SFML/Graphics.h>
#include "graphics.h"

size_t CalcPointsDistance(size_t x_1, size_t y_1, size_t x_2, size_t y_2)
{
    return (size_t)sqrt((x_1 - x_2) * (x_1 - x_2) + (y_1 - y_2) * (y_1 - y_2));
}

void ParsePressButton(size_t x, size_t y)
{
    printf("X_COORD: %lu\n Y_COORD: %lu\n\n", x, y);

    size_t distance = CalcPointsDistance(x, y, 
                                       BLUE_TABLET_X_CENTRE, BLUE_TABLET_Y_CENTRE);

    if (distance < BLUE_TABLET_RADIUS)
    {
        printf("BLUE\n");
        return;
    }
        
    distance = CalcPointsDistance(x, y, 
                                  RED_TABLET_X_CENTRE, RED_TABLET_Y_CENTRE);

    if (distance < RED_TABLET_RADIUS)
    {
        printf("RED\n");
        return;
    }
}

void PrintPicture()
{
    
    sfVideoMode window_mode = {WIDTH, HEIGHT, 32};
    sfUint32 style = sfTitlebar | sfClose;

    sfRenderWindow* window = sfRenderWindow_create( window_mode,
                                                    "Patcher",                    
                                                    style,                
                                                    NULL);

    sfTexture* font_texture = sfTexture_createFromFile("fonts/matrix.jpg", NULL);
    sfSprite* font_sprite = sfSprite_create();
    sfSprite_setTexture(font_sprite, font_texture, sfTrue);
    
    sfVector2u texSize = sfTexture_getSize(font_texture);

    sfSprite_setScale(font_sprite, 
                     (sfVector2f){ WIDTH  / (float)texSize.x,
                                   HEIGHT / (float)texSize.y
                                 });

    sfEvent event = {};

    while (sfRenderWindow_isOpen(window)) {
        while (sfRenderWindow_pollEvent(window, &event)) {

            if (event.type == sfEvtClosed)
            {
                sfRenderWindow_close(window);
                break;   
            }

            if (event.type == sfEvtMouseButtonPressed)
            {
                ParsePressButton((size_t)event.mouseButton.x, (size_t)event.mouseButton.y);
                break;
            }
        }

        sfRenderWindow_drawSprite(window, font_sprite, NULL);
        sfRenderWindow_display(window);
    }

    sfRenderWindow_destroy(window);
}