#ifndef PRINT_TEXT_H_
#define PRINT_TEXT_H_

#define CHAR_WIDTH 14
#define CHAR_HEIGHT 14
#include "stdint.h"

uint32_t* get_char_bitmap(char c)
{
    return chars[c];
}

void PrintChar(char c, int x, int y)
{
    rysowanie_ekran(get_char_bitmap(c), x, y, CHAR_HEIGHT, CHAR_WIDTH);
}

void PrintText(const char* text, int len, int x, int y)
{
    for(int i = 0; i < len; ++i)
    {
        PrintChar(text[i], i * CHAR_WIDTH + x, y);
    }
}

#endif /* PRINT_TEXT_H_ */
