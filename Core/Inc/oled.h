#include <stdint.h>
#include "fonts.h"
#include "stm32f4xx_hal.h"

#ifndef OLED_H
#define OLED_H

#define OLED_I2C_ADDR        0x78
#define OLED_WIDTH           128
#define OLED_HEIGHT          64

#define OLED_STRING_VSPACE   8

extern I2C_HandleTypeDef hi2c1;

typedef enum {
	BLACK = 0x0,
	WHITE = 0x1
} OLED_color;

typedef struct {
	uint16_t curr_x;
	uint16_t curr_y;
} OLED_state;


void OLED_init(void);
void OLED_update(void);
void OLED_set_cursor(uint16_t x, uint16_t y);
void OLED_draw_pixel(uint16_t x, uint16_t y, OLED_color color);
void OLED_fill(OLED_color color);
void OLED_draw_char(const char c, font font, OLED_color color);
void OLED_draw_string(char const* str, font font, OLED_color color);

#endif
