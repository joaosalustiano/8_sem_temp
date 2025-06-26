#define F_CPU   16000000
#include <util/delay.h>
#include <avr/io.h>

char digitos7seg[16] = {    0x3F, 0x06, 0x5B, 0x4F, 
                            0x66, 0x6D, 0x7D, 0x07, 
                            0x7F, 0x6F, 0x77, 0x7C, 
                            0x39, 0x5E, 0x79, 0x3F,  };

void disp7seg_init( void )
{
    DDRD  = 0xFF;
    PORTD = 0x00;
    DDRB |= (1<<0);
    DDRB |= (1<<1);
    PORTB &=~(1<<0);
    PORTB &=~(1<<1);
}

void disp7seg_unidade( unsigned char u )
{
    
	PORTB &=~(1<<1); // DESLIGA DEZENA
	PORTD = digitos7seg[u%10];
	PORTB |=(1<<0); // LIGANDO O UNIDADE

}

void disp7seg_dezena( unsigned char d )
{

	PORTB &=~(1<<0); // DESLIGANDO UNIDADE
	PORTD = digitos7seg[(d/10)%10];
	PORTB |=(1<<1); // LIGANDO DEZENA

}

void disp7seg_sbu()
{
	PORTB &=~(1<<1); // DESLIGA DEZENA
	PORTD = 0x40;
	PORTB |=(1<<0); // LIGANDO O UNIDADE
}

void disp7seg_sbd()
{
	PORTB &=~(1<<0); // DESLIGANDO UNIDADE
	PORTD = 0x40;
	PORTB |=(1<<1); // LIGANDO DEZENA
}
	