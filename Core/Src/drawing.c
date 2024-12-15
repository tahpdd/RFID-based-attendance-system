#include "sdram_cfg.h"
#include "ltdc_cfg.h"

#define MAKE_RGB(R,G,B) (uint16_t)(((R & 0x1F) << 11) | ((G & 0x3F) << 5) | (B & 0x1F))

#define COLOR_BLACK     MAKE_RGB(0,0,0)
void Draw_Pixel(uint16_t x, uint16_t y, uint16_t color)
{
    if ((x >= 0) && (x < LCD_ACTIVE_WIDTH) && (y >= 0) && (y < LCD_ACTIVE_HEIGHT))
    {
        *((uint16_t *) (SDRAM_BASE + (x * PIXEL_WIDHT) + (y * (LCD_ACTIVE_WIDTH * PIXEL_WIDHT)))) = color;
    }
}

void Draw_Circle(uint16_t xc, uint16_t yc, uint16_t radius, uint16_t color)
{
    for(int16_t y1=-radius; y1<=radius; y1++)
    {
        for(int16_t x1=-radius; x1<=radius; x1++)
        {
            if(x1*x1+y1*y1 <= radius*radius)
            {
                Draw_Pixel(x1+xc, y1+yc, color);
            }
        }
    }
}

extern const unsigned char Font[]; // �?m b?o khai b�o Font l� extern n?u Font du?c d?nh nghia ? noi kh�c.

void Draw_Char(uint16_t x, uint16_t y, char ch, uint16_t color, uint16_t bgColor) {
    if (ch < 32 || ch > 126) return; // Ch? x? l� k� t? ASCII t? 32 d?n 126

    const unsigned char *bitmap = &Font[(ch - 32) * 5]; // L?y bitmap cho k� t? t? Font
    for (uint8_t i = 0; i < 5; i++) { // Duy?t qua 5 c?t c?a k� t?
        uint8_t line = bitmap[i];
        for (uint8_t j = 0; j < 8; j++) { // Duy?t qua 8 d�ng (7 pixel v� 1 pixel tr?ng)
            if (line & 0x01) {
                Draw_Pixel(x + i, y + j, color); // V? pixel n?u bit 1
            } else {
                Draw_Pixel(x + i, y + j, bgColor); // V? pixel n?n n?u bit 0
            }
            line >>= 1; // Chuy?n sang d�ng ti?p theo trong bitmap
        }
    }
}



void Draw_String(uint16_t x, uint16_t y, const char *str, uint16_t color, uint16_t bgColor)
{
    while (*str) {
        Draw_Char(x, y, *str, color, bgColor);
        x += 6;
        str++;
    }
}

void Fill_Black(uint16_t startX, uint16_t endX, uint16_t startY, uint16_t endY)
{
	for (uint16_t y = startY; y < endY; y++) {
		for (uint16_t x = startX; x < endX; x++) {
			Draw_Pixel(x, y, COLOR_BLACK);
		}
	}
}
