#include <p18f4620.h>
#include <delays.h>

void isr (void) ;

#pragma code vector=0x08
void interrupt_vector(void) { 
   _asm 
   GOTO isr 
   _endasm 
} 

#pragma code /* vuelve a la sección de código por defecto */ 
#pragma interrupt isr
#pragma config OSC = HS		//activo cristal externo
#pragma config PBADEN = OFF 		//convierto RB4 en digital


void isr (void) {
	PORTB=PORTB;
	
	if (PORTBbits.RB4 == 0 ){	//secuencia 3
		LATD= 0b0001100;
		Delay10KTCYx(20);
		LATD = 0x00;
		Delay10KTCYx(20);
		LATD = 0b0000011;
		Delay10KTCYx(20);
	}  

    if (PORTBbits.RB5 == 0 ){	//secuencia 1
		LATDbits.LATD1 = 1;
		Delay10KTCYx(10);
		LATDbits.LATD3 = 1;
		Delay10KTCYx(10);
		LATDbits.LATD1 = 0;
		LATDbits.LATD0 = 1;
		Delay10KTCYx(10);
		LATDbits.LATD3 = 0;
		LATDbits.LATD2 = 1;
		Delay10KTCYx(10);
	}

	if (PORTBbits.RB6 == 0 ){	//secuencia 2
		LATDbits.LATD0 = 1;
		Delay10KTCYx(10);
		LATDbits.LATD0 = 0;
		LATDbits.LATD1 = 1;
		Delay10KTCYx(10);
		LATDbits.LATD1 = 0;
		LATDbits.LATD2 = 1;
		Delay10KTCYx(10);
		LATDbits.LATD2 = 0;
		LATDbits.LATD3 = 1;
		Delay10KTCYx(20);
		LATDbits.LATD3 = 0;
		LATDbits.LATD2 = 1;
		Delay10KTCYx(10);
		LATDbits.LATD2 = 0;
		LATDbits.LATD1 = 1;
		Delay10KTCYx(10);
		LATDbits.LATD1 = 0;
		LATDbits.LATD0 = 1;
		Delay10KTCYx(10);
	}

	if (PORTBbits.RB7 == 0 ){	//secuencia 3
		LATD = 0b0001111;
		Delay10KTCYx(20);
		LATD = 0x00;
		Delay10KTCYx(20);
		LATD = 0b0001111;
		Delay10KTCYx(20);
	}

	else{
		LATDbits.LATD0 = 0;
		LATDbits.LATD1 = 0;
		LATDbits.LATD2 = 0;
		LATDbits.LATD3 = 0;	
	}

	INTCON2bits.RBPU = 0;
}


void main() {
	LATD = 0x00; //hago que todos estén en cero al comienzo
	TRISD = 0x00; //pongo el puerto como salida
	

    TRISB = 0xFF; //seteo el puerto B como entrada (FF=11111111)

    INTCONbits.GIE = 1;  // INTerrupt CONfig - Global Interrupt Enable
	INTCONbits.PEIE = 1; // INTerrupt CONfig - PEripheral Interrupt Enable
    INTCONbits.RBIE = 1; // INTerrupt CONfig - Register B Interrupt Enable

	INTCON2bits.RBPU = 0;	//activo el pull-up

   while(1);
}
