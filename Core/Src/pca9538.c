#include <sdk_usart.h>
#include "main.h"
#include "i2c.h"
#include "pca9538.h"

HAL_StatusTypeDef PCA9538_read_register(uint16_t addr, pca9538_regs reg, uint8_t* buf) {
	return HAL_I2C_Mem_Read(&hi2c1, addr | 1, reg, 1, buf, 1, 100);
}


HAL_StatusTypeDef PCA9538_write_register(uint16_t addr, pca9538_regs reg, uint8_t* buf) {
	return HAL_I2C_Mem_Write(&hi2c1, addr & 0xFFFE, reg, 1, buf, 1, 100);
}

HAL_StatusTypeDef PCA9538_read_config(uint16_t addr, uint8_t* buf) {
	HAL_StatusTypeDef ret = HAL_OK;
	uint8_t *buf_ptr = buf;

	for(uint8_t i=0; i<4; i++ ) {
		ret = PCA9538_read_register(addr, i, buf_ptr++);

		if(ret!=HAL_OK)
			return ret;
	}

	return ret;
}

HAL_StatusTypeDef PCA9538_check_default_config(uint16_t addr) {
	HAL_StatusTypeDef ret = HAL_OK;
	uint8_t buf[4];

	ret = PCA9538_read_config(addr, buf);
	if( ret != HAL_OK ){
		USART_transmit((uint8_t*)"Error: couldn't read default config\n");
	}
	else if ( buf[1] != 0xFF && buf[2] != 0xFF && buf[3] != 0xFF ) {
		USART_transmit((uint8_t*)"Erorr: non-reset config\n");
		USART_transmit(buf);
		ret = HAL_ERROR;
	}

	return ret;
}

HAL_StatusTypeDef PCA9538_read_inputs(uint16_t addr, uint8_t* buf) {
	return PCA9538_read_register(addr, INPUT_PORT, buf);
}


