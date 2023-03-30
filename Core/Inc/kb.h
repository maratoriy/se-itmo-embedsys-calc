#ifndef INC_KEYBOARD_H
#define INC_KEYBOARD_H

#define KB_ROWS 4
#define KB_COLS 3


uint8_t check_key();
HAL_StatusTypeDef keyboard_init(void);

#endif
