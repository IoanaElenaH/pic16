#ifndef LCD_H
#define	LCD_H
void init_LCD(void);
void lcd_write(unsigned char c);
void lcd_clear(void);
void lcd_goto(unsigned char pos);
void lcd_puts(char* s);
void lcd_putch(char c);
void delay_LCD(unsigned long t);
//void initializare_diacritice(void);
//void scrie_diacritice_in_CGRAM(char matrice[8], unsigned char pozitie_DDRAM,unsigned char *diacritic);
//void afisare_diacritice(unsigned char diacritic_afisat, unsigned char linia);
#endif
