#define F_CPU   16000000UL
#include <util/delay.h>
#include <avr/io.h>


#define Bt   PB5   
#define Vm   PC5   
#define Am   PC4   
#define Vd   PC3   
#define Vmp  PC2   
#define Vdp  PC1   



void semaforo_init(void)
{
    // Bt como entrada (PB5)
    DDRB &= ~(1 << Bt);    // Limpa bit → entrada
    PORTB |= (1 << Bt);    // Ativa pull-up interno (opcional)

	// Saídas: A1 a A5
	DDRC |= (1 << Vm) | (1 << Am) | (1 << Vd) | (1 << Vdp) | (1 << Vmp);
}

void amarelo()
{
	PORTC &= ~((1 << Vm) | (1 << Vd) | (1 << Vdp));
	PORTC |= ((1 << Am) | (1 << Vmp));
}

void vermelho()
{
	PORTC &= ~((1 << Am) | ( 1<< Vd) | (1 << Vmp));
	PORTC |= ((1 << Vm) | (1 <<Vdp));
}

void verde()
{
	PORTC &= ~((1 << Am) | ( 1<< Vm) | (1 << Vdp));
	PORTC |= ((1 << Vd) | (1 <<Vmp));
}

void pisca_vmp()
{
	PORTC &= ~(1 << Vdp);
	PORTC ^= (1 << Vmp);
}