#include"RS232.h"
/**********************FUNCIONES_DE_LA_COMUNICAION_USART***********************/
void EUSART()
{
     TXSTA.SYNC=0;         //EUSART en Modo Asincrono
     TXSTA.BRGH=0;        //EUSART en Baja Velocidad
     BAUDCTL.BRG16=0;     //Generador de 8bits para el Baud Rate

     SPBRG=25;            //2400 Bits/segundo,Baud Rate=2400

     RCSTA.SPEN=1;       //Habilitacion TX y RX como terminales del puerto serial
     RCSTA.CREN=1;      //Habilita recepccion
     TXSTA.TXEN=1;      //Habilitacion de la trasmicion y Trasmision

     PIE1.RCIE=1;        //Habilitacion de interrupcion por recepccion.
     INTCON.PEIE=1;      //Habilitacion de interrupcion por periferico.
     INTCON.GIE=1;       //Habilitacion Global de las interrupciones.

     TRISD=0;            //Puerto de salida
     TRISA.RA4=1;       //RA4 oomo entrada
}