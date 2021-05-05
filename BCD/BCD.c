#include <p18f4620.h>
#include <delays.h>

void isr (void) ;

#pragma code vector=0x08
void interrupt_vector(void) { 
   _asm 
   GOTO isr 
   _endasm } 

#pragma code /* vuelve a la sección de código por defecto */ 
#pragma interrupt isr
#pragma config PBADEN = OFF 		//convierto RB4 en digital

void isr (void) {
	LATD = 0x00;
	while (PORTBbits.RB4==0 && PORTBbits.RB5==0 && PORTBbits.RB6==0 && PORTBbits.RB7==0){	//0	
		LATD = 0b10111111;
	}
	LATD = 0x00;
	while (PORTBbits.RB4==1 && PORTBbits.RB5==0 && PORTBbits.RB6==0 && PORTBbits.RB7==0){	//1
		LATD = 0b10000110;
	}
	LATD = 0x00;
	while (PORTBbits.RB4==0 && PORTBbits.RB5==1 && PORTBbits.RB6==0 && PORTBbits.RB7==0){	//2
		LATD = 0b11011011;
	}
	LATD = 0x00;
	while (PORTBbits.RB4==1 && PORTBbits.RB5==1 && PORTBbits.RB6==0 && PORTBbits.RB7==0){	//3
		LATD = 0b11001111;
	}
	LATD = 0x00;
	while (PORTBbits.RB4==0 && PORTBbits.RB5==0 && PORTBbits.RB6==1 && PORTBbits.RB7==0){	//4
		LATD = 0b11100110;
	}
	LATD = 0x00;
	while (PORTBbits.RB4==1 && PORTBbits.RB5==0 && PORTBbits.RB6==1 && PORTBbits.RB7==0){	//5
		LATD = 0b11101101;
	}
	LATD = 0x00;
	while (PORTBbits.RB4==0 && PORTBbits.RB5==1 && PORTBbits.RB6==1 && PORTBbits.RB7==0){	//6
		LATD = 0b11111101;
	}
	LATD = 0x00;
	while (PORTBbits.RB4==1 && PORTBbits.RB5==1 && PORTBbits.RB6==1 && PORTBbits.RB7==0){	//7
		LATD = 0b10000111;
	}
	LATD = 0x00;
	while (PORTBbits.RB4==0 && PORTBbits.RB5==0 && PORTBbits.RB6==0 && PORTBbits.RB7==1){	//8
		LATD = 0b11111111;
	}
	LATD = 0x00;
	while (PORTBbits.RB4==1 && PORTBbits.RB5==0 && PORTBbits.RB6==0 && PORTBbits.RB7==1){	//9
		LATD = 0b11101111;
	}
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
