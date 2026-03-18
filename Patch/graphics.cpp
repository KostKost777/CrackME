#include <stdio.h>
#include <math.h>
#include <SFML/Graphics.h>
#include <assert.h>
#include "graphics.h"

void PlayMelody()
{
    system("play -q -n synth 0.15 square 330");
    system("play -q -n synth 0.15 square 330");  
    system("play -q -n synth 0.15 square 330");  
    system("play -q -n synth 0.3  square 262"); 
    system("play -q -n synth 0.15 square 294");  
    system("play -q -n synth 0.15 square 330");  
    system("play -q -n synth 0.3  square 349");  
    system("play -q -n synth 0.3  square 330");  
    system("play -q -n synth 0.15 square 330");
    system("play -q -n synth 0.15 square 330");  
    system("play -q -n synth 0.15 square 330");  
    system("play -q -n synth 0.3  square 262");
}

size_t CalcPointsDistance(size_t x_1, size_t y_1, size_t x_2, size_t y_2)
{
    return (size_t)sqrt((x_1 - x_2) * (x_1 - x_2) + (y_1 - y_2) * (y_1 - y_2));
}

TabletType ParsePressButton(size_t x, size_t y)
{
    //printf("X_COORD: %lu\n Y_COORD: %lu\n\n", x, y);

    size_t distance = 0;

    distance = CalcPointsDistance(x, y, 
                                  BLUE_TABLET_X_CENTRE, BLUE_TABLET_Y_CENTRE);

    if (distance < BLUE_TABLET_RADIUS) 
        return BLUE;
    
    distance = CalcPointsDistance(x, y, 
                                  RED_TABLET_X_CENTRE, RED_TABLET_Y_CENTRE);

    if (distance < RED_TABLET_RADIUS) 
        return RED;

    return UNKNOWN;
    
}

void SetFullScreenBackgroundScale(sfSprite* background_sprite, sfTexture* background_texture, 
                                  size_t width, size_t height)
{
    sfSprite_setTexture(background_sprite, background_texture, sfTrue);
    
    sfVector2u tex_size = sfTexture_getSize(background_texture);
    sfSprite_setScale(background_sprite, 
                     (sfVector2f){ (float)width  / (float)tex_size.x,
                                   (float)height / (float)tex_size.y
                                 });
}

sfText* CreateTextObject(const char* message, sfFont* font, sfColor color, int x, int y)
{
    assert(message);
    assert(font);

    sfText* text = sfText_create();

    sfText_setFont(text, font);
    sfText_setString(text, message);
    sfText_setCharacterSize(text, 100);
    sfText_setFillColor(text, color);
    sfText_setPosition(text, (sfVector2f){(float)x, (float)y});

    return text;
}

TabletType ShowUserInterface()
{
    TabletType tablet = UNKNOWN;

    sfVideoMode window_mode = {WIDTH, HEIGHT, 32};
    sfUint32 style = sfTitlebar | sfClose;

    sfRenderWindow* window = sfRenderWindow_create( window_mode,
                                                    "Patcher",                    
                                                    style,                
                                                    NULL);

    sfFont* font = sfFont_createFromFile("source/matrix.ttf");

    sfTexture* background_2_texture = sfTexture_createFromFile("source/nigga.jpg", NULL);
    sfSprite* background_2_sprite = sfSprite_create();
    SetFullScreenBackgroundScale(background_2_sprite, background_2_texture, 
                                 WIDTH, HEIGHT);

    sfText* text_2 = CreateTextObject("Patch was made.\n"
                                      "Excellent choice.",
                                      font, sfGreen, 200, 300); 

    sfTexture* background_1_texture = sfTexture_createFromFile("source/matrix.jpg", NULL);
    sfSprite* background_1_sprite = sfSprite_create();
    SetFullScreenBackgroundScale(background_1_sprite, background_1_texture, 
                                 WIDTH, HEIGHT);
    
    sfText* text_1 = CreateTextObject("Hello, this program can create a patch.\n"             
                                      "          Make your choice:",
                                      font, sfGreen, 200, 10);

    sfText* text_exit = CreateTextObject("EXIT",
                                         font, sfGreen, 510, 1000);

    sfText* text_crack = CreateTextObject("CRACK",
                                          font, sfGreen, 1350 , 1000);

    sfRenderWindow_drawSprite(window, background_1_sprite, NULL);
    sfRenderWindow_drawText(window, text_1, NULL);
    sfRenderWindow_drawText(window, text_exit, NULL);
    sfRenderWindow_drawText(window, text_crack, NULL);
    sfRenderWindow_display(window);

    sfEvent event = {};

    while (sfRenderWindow_isOpen(window)) 
    {
        while (sfRenderWindow_pollEvent(window, &event)) 
        {

            if (event.type == sfEvtClosed)
            {
                sfRenderWindow_close(window);
                break;   
            }

            if (event.type == sfEvtMouseButtonPressed)
            {
                tablet = ParsePressButton((size_t)event.mouseButton.x, 
                                                     (size_t)event.mouseButton.y);

                if (tablet == BLUE)
                {                          
                    sfRenderWindow_drawSprite(window, background_2_sprite, NULL);
                    sfRenderWindow_drawText(window, text_2, NULL);
                    sfRenderWindow_display(window);
                    PlayMelody();
                    sfRenderWindow_close(window);
                }

                if (tablet == RED)
                    sfRenderWindow_close(window);

                break;
            }
        }
    }

    sfFont_destroy(font);    
    sfText_destroy(text_1);   
    sfText_destroy(text_exit);   
    sfText_destroy(text_crack);   
    sfTexture_destroy(background_1_texture); 
    sfSprite_destroy(background_1_sprite);   
    sfText_destroy(text_2);   
    sfTexture_destroy(background_2_texture); 
    sfSprite_destroy(background_2_sprite);
    sfRenderWindow_destroy(window);

    return tablet;   
}