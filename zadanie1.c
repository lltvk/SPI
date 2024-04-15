#include <avr/io.h>
#include <util/delay.h>
void SPI_Init(void);
//#define F_CPU 160000000L
void SPI_Init() {
//настройка направления передачи данных для выводов MOSI, SCK, SS и PB4
DDRB=(1<<PB2)|(1<<PB3)|(1<<PB4)|(1<<PB5);
//разрешение работы SPI в режиме ведущего с частотой сигнала SCK, равной (F_CPU/16)
SPCR=(1<<SPE)|(1<<MSTR)|(1<<SPR0);
}
void SPI_MasterTransmit(char cData){
//запись данных в регистр SPDR
SPDR =cData;
//ожидание окончания передачи данных (установки бира SPIF в регистре SPSR)
while (!(SPSR &(1<<SPIF)));
}
int main(void){
//инициализация модуля SPI
SPI_Init();
//установка сигнала Reset сдвигового регистра в высокое(неактивное)состояние
PORTB|=(1<<4);
//передача байта, соответствующего цифре "2" на семисегментный индикатор
SPI_MasterTransmit(0b11001101);
//порядок битов в байте 76543210
// сегменты edcpbafg
return 0;
//порядок битов в байте
}