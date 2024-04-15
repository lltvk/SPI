//реализация бегущих букв abcdef
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
 //ОЖИДАНИЕ ОКОНЧАНИЯ ПЕРЕДАЧИ ДАННЫХ (УСТАНОВКИ БИТА SPIFВ РЕГИСТРЕ SPSR)
 while(!(SPSR & (1<<SPIF)));
}
int main(void)
{
 int i;
 // ИНИЦИАЛИЗАЦИЯ МОДУЛЯ SPI
SPI_Init();
PORTB |= (1<<4);
// одномерный массив значений цифр семисегментного индикатора
int arr[7] = {0b00000100,0b00001000, 0b00100000,0b01000000, 
0b10000000,0b00000010,0b00000001};
while(1) {
for(int i = 0; i <= 7; i = i + 1)
{
SPI_MasterTransmit(arr[i]);
_delay_ms(200);
}}
 return 0;
