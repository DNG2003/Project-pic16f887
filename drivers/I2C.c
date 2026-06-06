#include "I2C.h"

void I2C_init(void)                /* Inicializar 2c */
{
     I2C_Port();                    // Configuracion de Direccion de terminales
     SSPCON|=Master_Mode_Clock;     //Modo Maestro con control de Reloj
     SSPCON.SSPEN=1;               //Habilitacion el Modulo MSSP en modo I2C
     SSPADD=SSPADD_Speed;          //Velocidad del I2C
     SSPSTAT.SMP=1;                //control de Velocidad inabilitado

}

void I2C_port(void)                  /*Configura puerto para 12c*/
{
     //Configurar terminales SCL y SDA como entradas
     SCL_Dir=1;           // Salida de Reloj
     SDA_Dir=1;          //Entrada/Salida de Reloj

}

void I2C_wait(void)     /* Espera a que las funciones terminen*/
{
     while(SSPSTAT.R_W|SSPCON2.ACKEN|SSPCON2.RCEN|SSPCON2.PEN
            |SSPCON2.RSEN|SSPCON2.SEN);
     return;
}
void I2C_start(void)
{
     SSPCON2.SEN=1;           // Inicia comunicacion
     I2C_wait();
}
void I2C_restart(void)
{
   SSPCON2.RSEN=1;    //reinicio de comunicacion
   I2C_wait();
}

void I2C_stop(void)
{
    SSPCON2.PEN=1;    //Paro de comunicacion
   I2C_wait();



}
void I2C_write(unsigned char Data)
{
    SSPBUF=Data;    //Direccion o Dato al SSPBUF
    I2C_wait();

}
unsigned char I2C_read(unsigned char Ack)
{
     unsigned char buffer;
     I2C_wait();
     SSPCON2.RCEN=1;     //Inicio de recepcion
     I2C_Wait();

     buffer=SSPBUF;
     I2C_wait();
     SSPCON2.ACKDT=Ack;       //Recibe el Acknowledge
     SSPCON2.ACKEN=1;         //Habilita el envio del acknowledge

     return buffer;

}