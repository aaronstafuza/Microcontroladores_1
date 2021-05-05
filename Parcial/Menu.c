#pragma config OSC = HSPLL      // Oscillator Selection bits (HS oscillator, PLL enabled (Clock Frequency = 4 x FOSC1))
#pragma config PWRT = OFF       // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = SBORDIS  // Brown-out Reset Enable bits (Brown-out Reset enabled in hardware only (SBOREN is disabled))
#pragma config WDT = OFF        // Watchdog Timer Enable bit (WDT enabled)
#pragma config MCLRE = ON       // MCLR Pin Enable bit (MCLR pin enabled; RE3 input pin disabled)

#include <p18f4620.h>
#include <stdlib.h>
#include <stdio.h>
#include <usart.h>
#include <delays.h>

//VARIABLES
int pote,poteh;
float angulo,porcentaje;
volatile int tiempo;

//INTERRUPCIÓN
void high_isr (void);		//Declaro la funcion de interrupcion

#pragma code high_vector=0x08		//Escribo en la posicion de memoria de la interrupcion alta
void interrupt_at_high_vector(void)	//Funcion ubicada en 0x08, que lleva a la rutina de interrupcion
	{
	_asm GOTO high_isr _endasm		//Ir a la funcion high_isr, rutina de interrupcion
	}

#pragma code						//Para ubicar el siguiente codigo donde debe ir
#pragma interrupt high_isr			//Compilar el codigo de la funcion nombrada como interrupcion de alto nivel

void high_isr (void)
{
    if(INTCONbits.TMR0IF == 1)	//interrupción timer0
    {
		T0CONbits.TMR0ON = 0;			// paro timer0
		T1CONbits.TMR1ON = 0;			// paro timer1
		WriteTimer0(15535);			// cargo 20ms al timer0

		LATDbits.LATD0 = 1;		// levanto los pines del servo
		LATDbits.LATD1 = 1;
		LATDbits.LATD2 = 1;
		LATDbits.LATD3 = 1;

		INTCONbits.TMR0IF = 0;		// flag del timer0 en 0
		tiempo=((pote*(-19.5015))+62800.0);	// calculo tiempo de timer1
		WriteTimer1(tiempo);				// cargo timer1 dependiendo del valor del potenciómetro
		
		T0CONbits.TMR0ON = 1;		// arranco ambos timers
		T1CONbits.TMR1ON = 1;
    }

    if(PIR1bits.TMR1IF == 1)	//interrupción timer1
	{
		LATDbits.LATD0 = 0;		// bajo los pines del servo
		LATDbits.LATD1 = 0;
		LATDbits.LATD2 = 0;
		LATDbits.LATD3 = 0;

		PIR1bits.TMR1IF=0;		// flag del timer1 en 0
    }

	if(pote == 1023)			// prendo LED rojo
	{
		LATDbits.LATD4 = 1;
		LATDbits.LATD5 = 0;
		LATDbits.LATD6 = 0;
	}
		
	if(pote == 0)				// prendo LED azul
	{
		LATDbits.LATD4 = 0;
		LATDbits.LATD5 = 1;
		LATDbits.LATD6 = 0;
	}
	
	if(460<pote && pote<563)	// prendo LED amarillo
	{
		LATDbits.LATD4 = 0;
		LATDbits.LATD5 = 0;
		LATDbits.LATD6 = 1;
	}
}


int main(void)
{
	PORTD = 0b00000000;
    TRISD = 0b00000000;		// pines como salida
	TRISA = 0b00000010;		// 1 pin como input (A1)

	RCONbits.IPEN = 0;		// Disable priority levels on interrupts
    INTCONbits.GIE = 1;		// interrupciones globales
	INTCONbits.PEIE = 1;	// Enable peripherical interrupt (activo para tener el segundo timer)
	INTCONbits.TMR0IE = 1; 	// habilitacion interrupcion del Timer 0 (el largo)
    PIE1bits.TMR1IE = 1; 	// habilitacion interrupcion del Timer 1 (el corto)

	T0CON = 0b00010001;		// timer0 usa el prescaler 1:4
	WriteTimer0(15535);		// cargo 20ms al timer0
	T1CON = 0b10000000;		// timer1 no usa prescaler (1:1)
	WriteTimer1(62600);		// cargo 0.3ms al timer1

	T0CONbits.TMR0ON = 1; 	// arrancan los timers
    T1CONbits.TMR1ON = 1;
	
	OpenUSART (USART_TX_INT_OFF &			// inicialización de USART
					USART_RX_INT_OFF &
					USART_ASYNCH_MODE &
					USART_EIGHT_BIT &
					USART_CONT_RX &
					USART_BRGH_LOW, 64);
 		

	ADCON0=0b00000101;		// seleccion canal AN1 y habilito el AD 	
	ADCON1=0b00001101;		// AN1 como analógica
	ADCON2=0b10000001;		// justifico a la derecha para usar 10 bits

	while(1)
	{
		ADCON0bits.GO = 1;	// activo AD

		while(ADCON0bits.DONE);

		poteh = ADRESH;		// guardo el ADRESH
		pote = (poteh<<8) + ADRESL;	// desplazo poteh 8 bits y le sumo el ADRESL asi uso 10bits
		angulo = ((pote*180.0/1023.0)-90.0); // calculo angulo del servo
		porcentaje = (angulo+90)*100/180;	// porcentaje del ángulo girado
		printf("Potenciometro: %d  \r\nAngulo: %d  \r\nPorcentaje: %d%% \r\n\r\n",pote,(int)angulo,(int)porcentaje); // imprimo en USART
		Delay10KTCYx(3000);
	}
}