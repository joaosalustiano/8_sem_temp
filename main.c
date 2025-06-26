#define F_CPU   16000000UL
#define Bt   PB5

#include <util/delay.h>
#include <avr/io.h>
#include "semaforo.h"
#include "disp7seg.h"


int main (void)
{
	unsigned int c = 0;
	semaforo_init();
	disp7seg_init();
	
	while ( 1 )
	{
		
		char i = 15;
		long t = 0;
			
		if (c < 3000)
		{
			amarelo();
			while ( c <= 3000 )
			{	
				if( c%2 )
				{
					disp7seg_sbu();
				}
				else
				{
					disp7seg_sbd();
				}
			
				_delay_ms(1);
				c++;
			}
		}
		else if (c < 18000)
		{
			vermelho();
	
			while ( c <= 18000 )
			{
				if( c%2 )
				{
					disp7seg_unidade( i );
				}
				else
				{
					disp7seg_dezena( i );
				}
			
				_delay_ms(1);
				c++;
	
				if(( c % 1000 )==0)
				{
					i = --i%100;
			
				}
				if (c >= 15000)
				{
					if( (c % 500) == 0)
					{
						pisca_vmp();
				
					}
				}
			}
		}
		
		else if (c < 60000)
		{
			PORTB &=~(1<<1);
			verde();
			while ( c <= 60000 )
			{	
				if( c%2 )
				{
					disp7seg_sbu();
				}
				else
				{
					disp7seg_sbd();
				}
			
				_delay_ms(1);
				c++;
				
				if(c < 50000 && ( !(PINB & (1 << Bt))))
				{
					c = 50000;
				}
			}
		}
		else
		{
			c = 0;  
		}
		
		_delay_ms(1);
		c++;
		
	}
}