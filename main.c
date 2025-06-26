#define F_CPU   16000000UL      
#define Bt   PB5                   

#include <util/delay.h>
#include <avr/io.h>
#include "semaforo.h"              
#include "disp7seg.h"              

int main (void)
{
    unsigned int c = 0;            // Contador de tempo base
    semaforo_init();               // Inicializa os pinos e estados do semáforo
    disp7seg_init();               // Inicializa o display de 7 segmentos
    
    while (1)
    {
        char i = 15;               // Contador regressivo para o vermelho
        long t = 0;                

        // Fase amarela (até 3000 ms)
        if (c < 3000)
        {
            amarelo();             // Liga o LED amarelo
            while (c <= 3000)
            {
                // Alterna entre segmentos superiores e inferiores do display
                if (c % 2)
                {
                    disp7seg_sbu();
                }
                else
                {
                    disp7seg_sbd();
                }

                _delay_ms(1);      // Aguarda 1 ms
                c++;               // Incrementa o contador de tempo
            }
        }

        // Fase vermelha (de 3001 até 18000 ms)
        else if (c < 18000)
        {
            vermelho();            // Liga o LED vermelho
            
            while (c <= 18000)
            {
                // Alterna entre mostrar unidade e dezena no display
                if (c % 2)
                {
                    disp7seg_unidade(i);
                }
                else
                {
                    disp7seg_dezena(i);
                }

                _delay_ms(1);
                c++;

                // A cada 1000 ms decrementa o contador 'i
                if ((c % 1000) == 0)
                {
                    i = --i % 100;
                }

                // Quando restam 3 segundos, começa a piscar o vermelho
                if (c >= 15000)
                {
                    if ((c % 500) == 0)
                    {
                        pisca_vmp();   // Pisca o vermelho e o amarelo juntos
                    }
                }
            }
        }

        // Fase verde (de 18001 até 60000 ms)
        else if (c < 60000)
        {
            PORTB &= ~(1 << 1);   
            verde();               // Liga o LED verde

            while (c <= 60000)
            {
                // Alterna entre os segmentos do display
                if (c % 2)
                {
                    disp7seg_sbu();
                }
                else
                {
                    disp7seg_sbd();
                }

                _delay_ms(1);
                c++;

                // Se o botão for pressionado antes de 50 segundos, força o fim da fase verde
                if (c < 50000 && !(PINB & (1 << Bt)))
                {
                    c = 50000;
                }
            }
        }

        // Reinicia o ciclo
        else
        {
            c = 0;
        }

        _delay_ms(1);  //Atraso
        c++;
    }
}
