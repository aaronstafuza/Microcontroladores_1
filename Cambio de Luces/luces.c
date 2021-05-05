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
	int c=0;			//bandera
	LATD = 0x00;				//apago todo
	while (c<30){
		c=1*LATDbits.LATD0+2*LATDbits.LATD1+3*LATDbits.LATD2+4*LATDbits.LATD3+5*LATDbits.LATD4+6*LATDbits.LATD5+7*LATDbits.LATD6+8*LATDbits.LATD7;	//coloco c en la luz que esta activada
	    if (PORTBbits.RB6 == 0){				//llevo a c a la secuencia 2
			c=c+10;
		}
		if (PORTBbits.RB7 == 0){	//secuencia 1
			while( c < 10 ){
				if (c==0){
					LATDbits.LATD0 = 1;
					Delay10KTCYx(20);
					c++;
					if (PORTBbits.RB6 == 0){		//llevo a c a la secuencia 2
						c=c+10;
					}
					if (PORTBbits.RB5 == 0){		//llevo a c al stop
						c=c+20;
					}
					if (PORTBbits.RB4 == 0){		//saco a c del while
						c=c+30;
					}
				}	
				if (c==1){
					LATDbits.LATD0 = 0;
					LATDbits.LATD1 = 1;
					Delay10KTCYx(20);
					c++;
					if (PORTBbits.RB6 == 0){
						c=c+10;
					}
					if (PORTBbits.RB5 == 0){
						c=c+20;
					}
					if (PORTBbits.RB4 == 0){
						c=c+30;
					}
				}
				if (c==2){
					LATDbits.LATD1 = 0;
					LATDbits.LATD2 = 1;
					Delay10KTCYx(20);
					c++;
					if (PORTBbits.RB6 == 0){
						c=c+10;
					}
					if (PORTBbits.RB5 == 0){
						c=c+20;
					}
					if (PORTBbits.RB4 == 0){
						c=c+30;
					}
				}
				if (c==3){
					LATDbits.LATD2 = 0;
					LATDbits.LATD3 = 1;
					Delay10KTCYx(20);
					c++;
					if (PORTBbits.RB6 == 0){
						c=c+10;
					}
					if (PORTBbits.RB5 == 0){
						c=c+20;
					}
					if (PORTBbits.RB4 == 0){
						c=c+30;
					}
				}
				if (c==4){
					LATDbits.LATD3 = 0;
					LATDbits.LATD4 = 1;
					Delay10KTCYx(20);
					c++;
					if (PORTBbits.RB6 == 0){
						c=c+10;
					}
					if (PORTBbits.RB5 == 0){
						c=c+20;
					}
					if (PORTBbits.RB4 == 0){
						c=c+30;
					}
				}
				if (c==5){
					LATDbits.LATD4 = 0;
					LATDbits.LATD5 = 1;
					Delay10KTCYx(20);
					c++;
					if (PORTBbits.RB6 == 0){
						c=c+10;
					}
					if (PORTBbits.RB5 == 0){
						c=c+20;
					}
					if (PORTBbits.RB4 == 0){
						c=c+30;
					}
				}
				if (c==6){
					LATDbits.LATD5 = 0;
					LATDbits.LATD6 = 1;
					Delay10KTCYx(20);
					c++;
					if (PORTBbits.RB6 == 0){
						c=c+10;
					}
					if (PORTBbits.RB5 == 0){
						c=c+20;
					}
					if (PORTBbits.RB4 == 0){
						c=c+30;
					}
				}
				if (c==7){
					LATDbits.LATD6 = 0;
					LATDbits.LATD7 = 1;
					Delay10KTCYx(20);
					c++;
					if (PORTBbits.RB6 == 0){
						c=c+10;
					}
					if (PORTBbits.RB5 == 0){
						c=c+20;
					}
					if (PORTBbits.RB4 == 0){
						c=c+30;
					}
				}
				if (c==8){
					LATDbits.LATD7 = 0;
					LATDbits.LATD0 = 1;
					Delay10KTCYx(20);
					c=1;
					if (PORTBbits.RB6 == 0){
						c=c+10;
					}
					if (PORTBbits.RB5 == 0){
						c=c+20;
					}
					if (PORTBbits.RB4 == 0){
						c=c+30;
					}
				}
			}
		}

		while( c >=10 && c<20 ){			//secuencia 2
				if (c==18){
					LATDbits.LATD0 = 0;
					LATDbits.LATD7 = 1;
					Delay10KTCYx(20);
					c--;
					if (PORTBbits.RB7 == 0){
						c=c-10;
					}
					if (PORTBbits.RB5 == 0){
						c=c+10;
					}
					if (PORTBbits.RB4 == 0){
						c=c+30;
					}
				}	
				if (c==17){
					LATDbits.LATD7 = 0;
					LATDbits.LATD6 = 1;
					Delay10KTCYx(20);
					c--;
					if (PORTBbits.RB7 == 0){
						c=c-10;
					}
					if (PORTBbits.RB5 == 0){
						c=c+10;
					}
					if (PORTBbits.RB4 == 0){
						c=c+30;
					}
				}
				if (c==16){
					LATDbits.LATD6 = 0;
					LATDbits.LATD5 = 1;
					Delay10KTCYx(20);
					c--;
					if (PORTBbits.RB7 == 0){
						c=c-10;
					}
					if (PORTBbits.RB5 == 0){
						c=c+10;
					}
					if (PORTBbits.RB4 == 0){
						c=c+30;
					}
				}
				if (c==15){
					LATDbits.LATD5 = 0;
					LATDbits.LATD4 = 1;
					Delay10KTCYx(20);
					c--;
					if (PORTBbits.RB7 == 0){
						c=c-10;
					}
					if (PORTBbits.RB5 == 0){
						c=c+10;
					}
					if (PORTBbits.RB4 == 0){
						c=c+30;
					}
				}
				if (c==14){
					LATDbits.LATD4 = 0;
					LATDbits.LATD3 = 1;
					Delay10KTCYx(20);
					c--;
					if (PORTBbits.RB7 == 0){
						c=c-10;
					}
					if (PORTBbits.RB5 == 0){
						c=c+10;
					}
					if (PORTBbits.RB4 == 0){
						c=c+30;
					}
				}
				if (c==13){
					LATDbits.LATD3 = 0;
					LATDbits.LATD2 = 1;
					Delay10KTCYx(20);
					c--;
					if (PORTBbits.RB7 == 0){
						c=c-10;
					}
					if (PORTBbits.RB5 == 0){
						c=c+10;
					}
					if (PORTBbits.RB4 == 0){
						c=c+30;
					}
				}
				if (c==12){
					LATDbits.LATD2 = 0;
					LATDbits.LATD1 = 1;
					Delay10KTCYx(20);
					c--;
					if (PORTBbits.RB7 == 0){
						c=c-10;
					}
					if (PORTBbits.RB5 == 0){
						c=c+10;
					}
					if (PORTBbits.RB4 == 0){
						c=c+30;
					}
				}
				if (c==11){
					LATDbits.LATD1 = 0;
					LATDbits.LATD0 = 1;
					Delay10KTCYx(20);
					c--;
					if (PORTBbits.RB7 == 0){
						c=c-10;
					}
					if (PORTBbits.RB5 == 0){
						c=c+10;
					}
					if (PORTBbits.RB4 == 0){
						c=c+30;
					}
				}
				if (c==10){
					LATDbits.LATD0 = 0;
					LATDbits.LATD7 = 1;
					Delay10KTCYx(20);
					c=17;
					if (PORTBbits.RB7 == 0){
						c=c-10;
					}
					if (PORTBbits.RB5 == 0){
						c=c+10;
					}
					if (PORTBbits.RB4 == 0){
						c=c+30;
					}
				}
		}
		while (c>=20 && c<30){				//stop
			if (PORTBbits.RB7 == 0){
					c=0;
			}
			if (PORTBbits.RB6 == 0){
					c=0;
			}
			if (PORTBbits.RB4 == 0){
					c=c+30;
			}
		}
	
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
