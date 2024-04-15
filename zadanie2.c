//поочередный вывод на семисегментный индикатор цифр от 0 до 9
#include <avr/io.h>
#include <util/delay.h>
void SPI_Init(void);
void SPI_Init(){
 // НАСТРОЙКА НАПРАВЛЕНИЯ ПЕРЕДА ДАННЫХ ДЛЯ ВЫВОДОВ MOSI, SCK, SS 
B PB4
 DDRB = (1<<PB2) | (1<<PB3) | (1<<PB4) | (1<<PB5);
 // РАЗРЕШЕНИЕ РАБОТЫ SPI В РЕЖИМЕ ВЕДУЩЕГО С ЧАСТОТОЙ СИГНАЛА SCK, РАВНОЙ (F_CPU/16)
 SPCR = (1<<SPE) | (1<<MSTR) | (1<<SPR0);
}
void SPI_MasterTransmit(char cData) {
 // ЗАПИСЬ ДАННЫХ В РЕГИСТР SPDR
 SPDR =cData;
 //ОЖИДАНИЕ ОКОНЧАНИЯ ПЕРЕДАЧИ ДАННЫХ (УСТАНОВКИ БИТА SPIFВ РЕГИСТРЕ SPSR)
 while(!(SPSR & (1<<SPIF)));
}
int main(void)
{
 int i;
 // ИНИЦИАЛИЗАЦИЯ МОДУЛЯ SPI
 SPI_Init();
 // УСТАНОВКА СИГНАЛА RESET СДВИГОВОГО РЕГИСТРА В ВЫСОКОЕ (НЕАКТИВНОЕ) СОСТОЯНИЕ
 PORTB |= (1<<4);
 unsigned char a[10] = {0b11111110, 0b00101000, 
0b11001101,0b01111101,0b00111011,0b01110111,0b11100111,0b00101100,0b11111111,0b01
111111};
 // ПЕРЕДАЧА БАЙТА, СООТВЕТСВУЮЩЕГО ЦИФРЕ НА СЕМИСЕГМЕНТНЫЙ ИНДИКАТОР
 SPI_MasterTransmit(0b11111111);
 while(1)
 {
 for (int i = 0; i<10; i++)
{
SPI_MasterTransmit(a[i]);
_delay_ms(1000);
}
 }
 return 0;
}
