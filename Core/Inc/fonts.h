#include "stm32f4xx_hal.h"

#ifndef FONTS_H
#define FONTS_H

typedef struct {
	const uint8_t font_width;
	const uint8_t font_height;
	const uint16_t *data;
} font;

extern font font_7x10;

#endif
