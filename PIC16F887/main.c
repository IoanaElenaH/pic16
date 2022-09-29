#include <xc.h>
#include "adc.h"
#include "dht.h"
#include  "lcd.h"
__PROG_CONFIG(1,0x20D4); 	// config. uC 
__PROG_CONFIG(2,0x0000); 	// config. uC 
#define LED1 RB0 
#define LED2 RB1
void init_uC(void); 
int time_of_day;
int analogtemp;
void main(void)
 {
	init_uC();
	init_LCD();
	init_ADC();
	

	while (1)
	{  
	 lcd_goto(0x80);
	 analogtemp=ADC_read(1); // facem conversia ADC si atribuirea o dam variabilei temperatura
	 analogtemp/=2; // am egalat valorile afisate pe LCD si cea data de senzor (la o simpla testare valoarea data de ADC era dubla fata de valoarea de la senzor)
     lcd_putch(analogtemp/10+ '0');
     lcd_putch(analogtemp%10 + '0');
     lcd_putch(223);
	 lcd_putch('C');
	 DHT11_read();
	 time_of_day=ADC_read(0); // facem conversia ADC si atribuirea o dam variabilei temperatura  
    	 if(time_of_day<300){
		lcd_goto(0x94);
		lcd_puts("TOD = DAY  ");
     	}
    	 else{
		lcd_goto(0x94);
		lcd_puts("TOD = NIGHT ");
	 }
     }
 }
 
 void init_uC (void) { 
	OSCCON 	= 0x71;			// setez Osc. intern uC de 8MHz // pag. 64
	TRISB 	= 0b00000000;	// tot Portul B este de iesire
	TRISD 	= 0b00000000;	// tot Portul B este de iesire
	TRISA = 0xFF;
} 
