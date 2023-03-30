#include "main.h"
#include "pca9538.h"
#include "kb.h"
#include "sdk_usart.h"
#include "usart.h"
#include <stdio.h>

#define KBRD_ADDR 0xE2

HAL_StatusTypeDef keyboard_init( void ) {
	HAL_StatusTypeDef ret = HAL_OK;

	uint8_t buf = 0;
	ret = PCA9538_write_register(KBRD_ADDR, POLARITY_INVERSION, &buf);
	if( ret != HAL_OK ) {
		USART_transmit((uint8_t*)"Error: Couldn't write polarity to KB\n");
		return ret;
	}

	buf = 0;
	ret = PCA9538_write_register(KBRD_ADDR, OUTPUT_PORT, &buf);
	if( ret != HAL_OK ) {
		USART_transmit((uint8_t*)"Error: Output error\n");
	}
	return ret;
}

static uint8_t rows_config[] = {0xFE, 0xFD, 0xFB, 0xF7};

uint8_t check_key() {
	HAL_StatusTypeDef ret = keyboard_init();
	if(ret != HAL_OK) {
		USART_transmit((uint8_t*)"Error: keyboard init\n");
	}

	for(size_t row = 0; row < KB_ROWS; row++) {
		uint8_t buf = rows_config[row];
		ret = PCA9538_write_register(KBRD_ADDR, CONFIG, &buf);
		if (ret!=HAL_OK) {
			USART_transmit((uint8_t*)"Error: setup keyboard config\n");
		}

		ret = PCA9538_read_inputs(KBRD_ADDR, &buf);
		if (ret!=HAL_OK) {
			USART_transmit((uint8_t*)"Error: reading keyboard input\n");
		}

		uint8_t key_col = buf & 0x70;
		if(key_col != 0x70) {
			for(uint8_t col = 0; col < KB_COLS; col++) {
				if(key_col & (1 << col)) {
					uint8_t key = row+col*KB_ROWS;
					char buf_str[18];
					sprintf(buf_str, "Pressed: %d key\n", key);
					USART_transmit((uint8_t*)buf_str);
					return key;
				}
			}
		}
	}
	return 0;
}
