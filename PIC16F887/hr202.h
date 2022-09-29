#ifndef LCD_H
#define	LCD_H
void init_LCD(void);
void lcd_write(unsigned char c);
void lcd_clear(void);
void lcd_goto(unsigned char pos);
void lcd_puts(char* s);
void lcd_putch(char c);
void delay_LCD(unsigned long t);
#endif
