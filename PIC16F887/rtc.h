

#ifndef RTC_H
#define	RTC_H

#include <stdint.h>

void I2C_Init(uint32_t i2c_clk_freq);
void I2C_Start();
void I2C_Repeated_Start();
void I2C_Stop();
void I2C_Write(uint8_t i2c_data);
uint8_t I2C_Read(uint8_t ack);
uint8_t bcd_to_decimal(uint8_t number);
uint8_t decimal_to_bcd(uint8_t number);
void RTC_display();
void RTC_Status(void);


#endif	/* RTC_H */

