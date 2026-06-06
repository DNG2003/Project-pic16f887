#include"Teclado.h"

void Teclado_Ini()
{

     ANSELH=0X00;      //Configuracion Entradas Digitales en PORTB
     Teclado_Dir=0xF0; //Nibble Alto Entrada|Bajo Salida
                        //C1 C2 C3 C4| F1 F2 F3 F4

}

unsigned char Tecla_Presionada()
{
    unsigned char Filas;   //Filas Teclado
    unsigned char CF;      //Columnas y Flles (0xCF) del Teclado
    volatile char TP;     //Tecla presionada

    for(Filas=0x01;Filas!=0x10;Filas<<=1)
    {
    Teclado_Out=Filas;    //Filas a puerto
    delay_ms(10);         // Evitar rebote(Bounce)
    CF=Teclado_In;        //Lectura del Teclado,Columnas y Filas
    
    switch(CF)
    {
     case 0x11:return TP='1'; break; //1
     case 0x21:return TP='2'; break; //2
     case 0x41:return TP='3'; break; //3
     case 0x81:return TP='A'; break; //A

     case 0x12:return TP='4'; break; //4
     case 0x22:return TP='5'; break; //5
     case 0x42:return TP='6'; break; //6
     case 0x82:return TP='B'; break; // B

     case 0x14:return TP='7'; break; //7
     case 0x24:return TP='8'; break; //8
     case 0x44:return TP='9'; break; //9
     case 0x84:return TP='C'; break; //C

     case 0x18:return TP='*'; break; //*
     case 0x28:return TP='0'; break; //0
     case 0x48:return TP='#'; break; //#
     case 0x88:return TP='D'; break; //D

    }
   }
   return(TP=16);  // Teclado sin presionar
}