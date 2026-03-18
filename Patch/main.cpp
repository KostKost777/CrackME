
#include <stdio.h>
#include <stdlib.h>
#include "graphics.h"
#include "patch.h"

int main(int argc, char* argv[])
{
    char* file_name = NULL;

    if (argc > 1)
        file_name = argv[1];

    TabletType user_choice = ShowUserInterface();

    if (user_choice == RED)
        return 0;

    int offset = 23;
    unsigned char new_bytes[] = {0x90, 0x90};

    if (user_choice == BLUE)
        MakePatch(file_name, offset, new_bytes, sizeof(new_bytes));

    return 0;
}

