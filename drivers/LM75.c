#include "LM75.h"
#include "I2C.h"

 int temperature;
 char Dec,Uni,Deci;
 
/**************************FUNCIONES DE I2C_ LM75******************************/

 void I2C_LM75R(void)// lectura con I2C en LM75
{
    unsigned char Temp_H, Temp_L; // Para almacenar los bytes del registro de temperatura
    volatile int temp;    // Para almacenar la temperatura
    // Lectura
    I2C_start();                 //Inicio Comunicacion
    I2C_write(LM75_W);           //Direccion +Write
    I2C_write(0x00);            //Dirección Inicial(Inicia Puntero del Esclavo)
    I2C_restart();               //Reinicio de Comunicación
    I2C_write(LM75_R);           //Dirección + Read
    Temp_H=I2C_read(ACK);        //Lectura de temperatur parte alta
    Temp_L=I2C_read(NACK);       //Lectura de temperatur parte baja
    I2C_stop();                  ////Fin de Comunicación

    // Combinar los bytes en un entero de 16 bits
    temp = (Temp_H << 8)|Temp_L;
    // Desplazar a la derecha 7 bits para eliminar los no usados
    temp = temp >> 7;
     // Convertir a temperatura en °C
    temperature = temp*0.5; // Cada incremento de 1 equivale a 0.5°C

 }

void Descomponer_Num(int data_temp)
{
    Dec=(data_temp/10);
    Uni=((data_temp%10)/1);
   // Deci=(((data_temp%10)%1)/1);
}