/*
 * i2c_driver.c
 *
 *  Created on: Aug 12, 2024
 *      Author: abdoul-karim.mahamad
 */

#include "stm32f412zx.h"
#include "i2c_driver.h"

#define I2C2_SDA    (1)
#define I2C2_CLK    (0)

uint8_t reg_state  = 0 ;


/**
 * @brief I2C Clock Configuration
 * @retval None
 *
 */
void _I2C2_CLK()
{
	debug("I2C2_CLK\r\n");
	RCC->APB1ENR |= RCC_APB1ENR_I2C2EN;
}

/**
 * @brief I2C init
 * @retval None
 *
 */
void Init_I2C2()
{
	debug("Init I2C\r\n");
	I2C2->CR1 = I2C_CR1_SWRST;    //RST
	I2C2->CR1 &= ~I2C_CR1_SWRST;
	I2C2->CR2 |= 0x10;
	I2C2->CCR |= 0x50;     //Standard mode
	I2C2->TRISE = 0x10;
	I2C2->CR1 |= I2C_CR1_PE;
}

/**
 * @brief GPIO Clock configuration
 * @retval None
 */
void _GPIO_CLK()
{
	debug("GPIO_CLK\r\n");
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOFEN;
}

/**
 * @brief GPIO init
 * @retval None
 *
 */
void Init_GPIO()
{
	debug("Init GPIO\r\n");
	GPIOF->MODER |= (0b10 << (I2C2_SDA *2)) | (0b10 << (I2C2_CLK));
	GPIOF->OTYPER |= (0b1 << (I2C2_SDA )) | (0b1 << (I2C2_CLK));
	GPIOF->OSPEEDR |= (0b11 << (I2C2_SDA *2)) | (0b11 << (I2C2_CLK*2));
	GPIOF->AFR[0] |= (0b0100 << (I2C2_CLK*4)) | (0b0100 << (I2C2_SDA*4));
}


/**
 * @brief i2c start bit generate
 * @retval None
 *
 */
void i2c_start_cond()
{

	debug("start \r\n");
	I2C2->CR1 |= I2C_CR1_START;

	while (!(I2C2->SR1 & I2C_SR1_SB));      // Start bit Ok
	reg_state =  I2C2->SR1 ;
}

/**
 * @brief i2c write address send by master to the slave
 * @retval 0
 *
 */
uint8_t i2c_send_address_W(uint8_t address)
{
	debug("write addr \r\n");
	I2C2->DR = address;
	while (!(I2C2->SR1 & I2C_SR1_ADDR));     // Slave address matched

	reg_state =  I2C2->SR1 ;
	reg_state =  I2C2->SR2 ;

	while (!(I2C2->SR1 & I2C_SR1_TXE));      //Data register empty
	return 0;

}


/**
 * @brief write i2c data
 * @retval None
 *
 */
void i2c_data_write(uint8_t *data, uint8_t length)
{
	debug("Write \r\n");
	for(int i; i< length; i++)
	{
		I2C2->DR = data[i];
		while (!(I2C2->SR1 & I2C_SR1_TXE));     //Data register empty
		while (!(I2C2->SR1 & I2C_SR1_BTF));     //Data Byte transfer finished
		reg_state =  I2C2->SR1 ;
		reg_state =  I2C2->SR2 ;

	}
}

/**
 * @brief i2c read send by the master
 * @retval None
 *
 */
uint8_t  i2c_send_address_R(uint8_t address)
{
	I2C2->DR = address;
	while (!(I2C2->SR1 & I2C_SR1_ADDR))    // Slave address matched
	{
		if((I2C2->SR1 & I2C_SR1_AF) == 1)
		{
			return 0;
		}
	}
	reg_state =  I2C2->SR1 | I2C2->SR2;   //clear
	return 0;

}

/**
 * @brief i2c read data from slave
 * @retval None
 *
 */
void i2c_data_read(char data[])
{
	I2C2->CR1 |= I2C_CR1_ACK;
	while (!(I2C2->SR1 & I2C_SR1_BTF));      //Data Byte transfer finished

}

/**
 * @brief i2c stop bit generate
 * @retval None
 *
 */
void i2c_stop()
{
	I2C2->CR1 |= I2C_CR1_STOP;
	reg_state =  I2C2->SR1 ;
	reg_state =  I2C2->SR2 ;
}

