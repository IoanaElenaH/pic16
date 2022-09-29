#include <xc.h>
#include "lcd.h"
#include "rtc.h"
#include <stdint.h>
#define _XTAL_FREQ 8000000
uint8_t  i, second, minute, hour, m_day, month, year;
 
/********************** I2C functions **************************/
void I2C_Init(uint32_t i2c_clk_freq)
{
  SSPCON  = 0x28;  // configure MSSP module to work in I2C mode
  SSPADD  = (_XTAL_FREQ/(4 * i2c_clk_freq)) - 1;  // set I2C clock frequency
  SSPSTAT = 0;
}
 
void I2C_Start()
{
  while ((SSPSTAT & 0x04) || (SSPCON2 & 0x1F));  // wait for MSSP module to be free (not busy)
  SEN = 1;  // initiate start condition
}
 
void I2C_Repeated_Start()
{
  while ((SSPSTAT & 0x04) || (SSPCON2 & 0x1F));  // wait for MSSP module to be free (not busy)
  RSEN = 1;  // initiate repeated start condition
}
 
void I2C_Stop()
{
  while ((SSPSTAT & 0x04) || (SSPCON2 & 0x1F));  // wait for MSSP module to be free (not busy)
  PEN = 1;  // initiate stop condition
}
 
void I2C_Write(uint8_t i2c_data)
{
  while ((SSPSTAT & 0x04) || (SSPCON2 & 0x1F));  // wait for MSSP module to be free (not busy)
  SSPBUF = i2c_data;  // update buffer
}
 
 uint8_t I2C_Read(uint8_t ack)
{
  uint8_t _data;
  while ((SSPSTAT & 0x04) || (SSPCON2 & 0x1F));  // wait for MSSP module to be free (not busy)
  RCEN = 1;
  while ((SSPSTAT & 0x04) || (SSPCON2 & 0x1F));  // wait for MSSP module to be free (not busy)
  _data = SSPBUF;  // read data from buffer
  while ((SSPSTAT & 0x04) || (SSPCON2 & 0x1F));  // wait for MSSP module to be free (not busy)
  // send acknowledge pulse ? (depends on ack, if 1 send, otherwise don't send)
  ACKDT = !ack;
  ACKEN = 1;
  return _data;  // return data read
}
 
/********************** end I2C functions **********************/
 
/********************** RTC chip functions *********************/
// convert BCD to decimal function
uint8_t bcd_to_decimal(uint8_t number) {
  return((number >> 4) * 10 + (number & 0x0F));
}
 
// convert decimal to BCD function
uint8_t decimal_to_bcd(uint8_t number) {
  return(((number / 10) << 4) + (number % 10));
}
 
// display time and date function
void RTC_display()
{
  static char Time[] = "TIME: 00:00:00";
  static char Date[] = "DATE: 00/00/2000";
 
  // convert data from BCD format to decimal format
  second = bcd_to_decimal(second);
  minute = bcd_to_decimal(minute);
  hour   = bcd_to_decimal(hour);
  m_day  = bcd_to_decimal(m_day);
  month  = bcd_to_decimal(month);
  year   = bcd_to_decimal(year);
  // end conversion
 
  // update time
  Time[6]  = hour   / 10 + '0';
  Time[7]  = hour   % 10 + '0';
  Time[9]  = minute / 10 + '0';
  Time[10] = minute % 10 + '0';
  Time[12] = second / 10 + '0';
  Time[13] = second % 10 + '0';
  // update date
  Date[6]  = m_day  / 10 + '0';
  Date[7]  = m_day  % 10 + '0';
  Date[9]  = month  / 10 + '0';
  Date[10] = month  % 10 + '0';
  Date[14] = year   / 10 + '0';
  Date[15] = year   % 10 + '0';
 
  lcd_goto(0x80);    // go to column 1, row 1
  lcd_puts(Time);   // print time
  lcd_goto(0xC0);    // go to column 1, row 2
  lcd_puts(Date);   // print date
}


void RTC_Status(void)
{
     // read current time and date from the RTC chip
    I2C_Start();           // start I2C
    I2C_Write(0xD0);       // RTC chip address
    I2C_Write(0);          // send register address
    I2C_Repeated_Start();  // restart I2C
    I2C_Write(0xD1);       // initialize data read
    second = I2C_Read(1);  // read seconds from register 0
    minute = I2C_Read(1);  // read minutes from register 1
    hour   = I2C_Read(1);  // read hour from register 2
    I2C_Read(1);           // read day from register 3 (not used)
    m_day  = I2C_Read(1);  // read date from register 4
    month  = I2C_Read(1);  // read month from register 5
    year   = I2C_Read(0);  // read year from register 6
    I2C_Stop();            // stop I2C
 
    RTC_display();    // print time & date
 
    __delay_ms(50);   // wait 50 ms
}
