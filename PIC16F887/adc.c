#include "adc.h"
#include <xc.h>
#define _XTAL_FREQ 8000000 // 8MHz
void init_ADC(void){
	
	ADCON0=0b01000001;// A/D Conversion Clock Fosc/32; ADC channel pe AN0 l; ADC enable
	ADCON1=0b10000000; // Right justified
}
int ADC_read(unsigned char channel){
     ADCON0&=0b11000011; 
     ADCON0|=channel<<2;
	__delay_ms(2);
    GO_nDONE = 1; 
    while(GO_nDONE); 
    return ((ADRESH<<8)+ADRESL);
}
