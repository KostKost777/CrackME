#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "patch.h"

void MakePatch(char* file_name, int offset, unsigned char* new_bytes, size_t amount)
{
    assert(file_name);
    assert(new_bytes);

    FILE* file = fopen(file_name, "rb+");
        
    fseek(file, offset, 0);

    fwrite(new_bytes, 1, amount, file);

    fclose(file);
}