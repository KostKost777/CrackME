
#include <stdio.h>
#include <stdlib.h>
#include <SFML/Graphics.h>
#include "graphics.h"

int main()
{
    PrintPicture();
    //MakePatch();
    return 0;
}

void MakePatch()
{
    const int OFFSET = 14;
    unsigned char patch_bytes[] = {0xEA, 0x25, 0x01, 0x88, 0x52};

    FILE* file = fopen("CRCK_BAY.COM", "rb+");
        
    fseek(file, OFFSET, 0);

    fwrite(patch_bytes, 1, sizeof(patch_bytes), file);

    fclose(file);
}