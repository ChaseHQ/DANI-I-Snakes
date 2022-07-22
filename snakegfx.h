#include <dani1/danivga.h>

#define GFX_TILECOUNT       10

#define GFX_SNAKEHEAD_UP    150
#define GFX_SNAKEHEAD_RIGHT 151
#define GFX_SNAKEHEAD_DOWN  152
#define GFX_SNAKEHEAD_LEFT  153
#define GFX_SNAKEBODY       154
#define GFX_SNAKETAIL_UP    155
#define GFX_SNAKETAIL_RIGHT 156
#define GFX_SNAKETAIL_DOWN  157
#define GFX_SNAKETAIL_LEFT  158
#define GFX_FOOD            159

#define GFX_START           GFX_SNAKEHEAD_UP

dvga_character gfx_tiles[GFX_TILECOUNT] = {
    {
        0b00100100,
        0b00011000,
        0b00111100,
        0b01111110,
        0b11011011,
        0b11111111,
        0b11111111,
        0b11111111
    },
    {
        0b11110000,
        0b11111000,
        0b11101101,
        0b11111110,
        0b11111110,
        0b11101101,
        0b11111000,
        0b11110000
        
    },
    {
        0b11111111,
        0b11111111,
        0b11111111,
        0b11011011,
        0b01111110,
        0b00111100,
        0b00011000,
        0b00100100
    },
    {
        0b00001111,
        0b00011111,
        0b10110111,
        0b01111111,
        0b01111111,
        0b10110111,
        0b00011111,
        0b00001111
    },
    {
        0b11111111,
        0b11111101,
        0b11011111,
        0b11111111,
        0b11111101,
        0b11111111,
        0b11101111,
        0b11111111
    },
    {
        0b11111111,
        0b11111111,
        0b01111110,
        0b01111110, /*snake tail up - 155*/
        0b00111100,
        0b00011000,
        0b00000000,
        0b00000000
    },
    {
        0b00000011,
        0b00001111,
        0b00011111,
        0b00111111,
        0b00111111,
        0b00011111,
        0b00001111,
        0b00000011
    },
    {
        0b00000000,
        0b00000000,
        0b00011000,
        0b00111100,
        0b01111110,
        0b01111110,
        0b11111111,
        0b11111111
    },
    {
        0b11000000,
        0b11110000,
        0b11111000,
        0b11111100,
        0b11111100,
        0b11111000,
        0b11110000,
        0b11000000
    },
    {
        0b00100100,
        0b01100110,
        0b00011000,
        0b00111100,
        0b01111110,
        0b01111110,
        0b01111110,
        0b00111100
    }
};