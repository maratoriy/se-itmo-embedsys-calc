#include "main.h"

#ifndef PCA9538_H
#define PCA9538_H

#define DIP_RD_ADDR 0xE1
#define DIP_WR_ADDR 0xE0

typedef enum{
	INPUT_PORT = 0x00,
	OUTPUT_PORT = 0x01, 
	POLARITY_INVERSION = 0x02, 
	CONFIG = 0x03 
}pca9538_regs;

typedef enum{
	LOW = 0,
	HIGH = 1
}what_bytes;

HAL_StatusTypeDef PCA9538_read_register(uint16_t addr, pca9538_regs reg, uint8_t* buf);
HAL_StatusTypeDef PCA9538_write_register(uint16_t addr, pca9538_regs reg, uint8_t* buf);
HAL_StatusTypeDef PCA9538_read_config(uint16_t addr, uint8_t* buf);
HAL_StatusTypeDef PCA9538_check_default_config(uint16_t addr);
HAL_StatusTypeDef PCA9538_read_inputs(uint16_t addr, uint8_t* buf);

#endif
