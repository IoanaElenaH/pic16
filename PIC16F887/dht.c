#include "dht.h"
#include <xc.h>
#include "lcd.h"

#define _XTAL_FREQ 8000000

char Check_bit;

void DHT11_request(void)
{
    TRISBbits.TRISB0=0; // PINUL 0 de pe PORTUL B este setat ca fiind de iesire
    DHT11_PIN=0;
    __delay_ms(18);
    DHT11_PIN=1;
    __delay_us(30);
    TRISBbits.TRISB0=1;; //pinul 0 devine de tip INPUT
}


void DHT11_response(void)
{
    __delay_us(40);
    if(DHT11_PIN == 0)
    {
        __delay_us(80);

        if(DHT11_PIN == 1)
        {
 
        }
        __delay_us(50);
    }
    
}


char DHT11_receive(void)
{
    char data=0;
    for(char i=0;i<8;i++)
    {
        while(!DHT11_PIN);
        __delay_us(30);
        if(DHT11_PIN)
        {
            data|=1<<(7-i);
        }
        while(DHT11_PIN);
    }
    return data;
    
}

void DHT11_read(void)
{
    DHT11_type DHT11_values;
    
    DHT11_request();
    DHT11_response();

        
        DHT11_values.Humidity_integer = DHT11_receive();
        DHT11_values.Humidity_decimal = DHT11_receive();
        DHT11_values.Temperature_integer = DHT11_receive();
        DHT11_values.Temperature_decimal = DHT11_receive();
        DHT11_values.Check_sum = DHT11_receive();
        
        lcd_goto(0x94);
        lcd_puts("H:");
        lcd_putch((DHT11_values.Humidity_integer/10)%10 + '0');
        lcd_putch(DHT11_values.Humidity_integer%10 + '0');
        lcd_putch('%');
        
        lcd_goto(0xD4);
        lcd_puts(" T:");
        lcd_putch(DHT11_values.Temperature_integer/10 + '0');
        lcd_putch(DHT11_values.Temperature_integer%10 + '0');
        lcd_putch(223);
        lcd_putch('C');


    __delay_ms(1000);
    
    
}



