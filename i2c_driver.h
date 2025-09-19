/*
 * i2c_driver.h
 *
 *  Created on: Aug 12, 2024
 *      Author: abdoul-karim.mahamad
 */

#ifndef INC_I2C_DRIVER_H_
#define INC_I2C_DRIVER_H_
#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f412zx.h"

void _I2C2_CLK();
void _GPIO_CLK();
void Init_I2C2();
void i2c_start_cond();
uint8_t i2c_send_address_W(uint8_t address);
uint8_t  i2c_send_address_R(uint8_t address);
void i2c_data_read(char data[]);
void i2c_data_write(uint8_t data);
void i2c_stop();

#ifdef __cplusplus
}
#endif
#endif /* INC_I2C_DRIVER_H_ */
