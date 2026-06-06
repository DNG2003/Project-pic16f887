#include"I2C.h"
#include"LCD.h"

/*********************VARIABLES_I2C_Ds1307*************************************/
 char Seg=0,Min=0,Hour=0,Day=0x01,Date=0x01,Month=0x01,Year=0x20,TDay=0;
 
 char Label1[]={"DATE:  /   /  ~ \n"};

void I2C_Ds1307W(void)  //Escritura con I2C en D81307
 {

    /* Escritura */
   // I2C_init();         //Configuracion MSSP
    I2C_start();        //Inicio Comunicacion
    I2C_write(Ds1307_W);  //Direoción + Write
    I2C_write(0x00);    //Direccion Inicial (Inicia Puntero del Esclavo)
    I2C_write(Seg);     //Escritura de Segundos (00-59)
    I2C_write(Min);     //Escriture de Minutos  (00-59)
    I2C_write(Hour);    //Esaritura de Horan (00-23)
    I2C_write(Day);     //Escritura de Dia de la Semana (01-07, Dom-Lun)
    I2C_write(Date);    //Escritura de Dia del Mes (00-31)
    I2C_write(Month); //Escritura de Mes (01-12)
    I2C_write(Year);  //Escritura de A-0 (00-99, 2000-2099)
    I2C_stop();
 }
 
 void Mostrar_lcd_DS1307()
{
        LCD_BCD_print(0x85,Date);    //fecha
        LCD_BCD_print(0x8C,Year);    //año
        LCD_BCD_print(0xC5,Hour);    // horas
        LCD_BCD_print(0xC8,Min);      // minutos
        LCD_BCD_print(0xCB,Seg);      //seg
}

/**************************FUNCIONES DE I2C_ DS1307****************************/

void I2C_Ds1307R(void)  //Lectura con 12C en Ds1307
{
    // Lectura
    I2C_start();                      //Inicio Comunicacion
    I2C_write(Ds1307_W);              //Direccion +Write
    I2C_write (0x00);                //Dirección Inicial(Inicia Puntero del Esclavo)
    I2C_restart();                    //Reinicio de Comunicsción
    I2C_write(Ds1307_R);              //Dirección + Read
    Seg=I2C_read(ACK);                //Lectura de Segundos
    Min=I2C_read(ACK);                //Lecturra de Minutos
    Hour=I2C_read(ACK);               //Lectura de Horas
    Day=I2C_read(ACK);                //Lectura de Día (Domingo...Sabado)
    Date=I2C_read(ACK);               //Lectura de Dia del Mes
    Month=I2C_read(ACK);              //Lectura de MES (Enero...Diciembre)
    Year=I2C_read(NACK);              //Lectura de Año
    I2C_stop();                       ////Fin de Comunicacion
    if(Day==0){Day=1;}

    if(TDay!=Day)
    {
            TDay=Day;
            switch(TDay)
            {
             case 1:Label1[15]='D';break;//Label1[13]='o';Label1[14]='m';break;
             case 2:Label1[15]='L';break;//Label1[13]= 'u';Label1[14]='n';break;
             case 3:Label1[15]='M';break;//Label1[13]= 'a';Label1[14]='r';break;
             case 4:Label1[15]='m';break;//Label1[13]= 'i';Label1[14]='e';break;
             case 5:Label1[15]='J';break;//Label1[13]='u';Label1[14]='e';break;
             case 6:Label1[15]='V';break;//Label1[13]= 'i';Label1[14]='e';break;
             case 7:Label1[15]='S';break;//Label1[13]= 'a';Label1[14]='b';break;

            }
            switch(Month)
            {
             case 0x01:Label1[8]='E';Label1[9]='n';Label1[10]='e';break;
             case 0x02:Label1[8]='F';Label1[9]= 'e';Label1[10]='b';break;
             case 0x03:Label1[8]='M';Label1[9]= 'a';Label1[10]='r';break;
             case 0x04:Label1[8]='A';Label1[9]= 'b';Label1[10]='r';break;
             case 0x05:Label1[8]='M';Label1[9]= 'a';Label1[10]='y';break;
             case 0x06:Label1[8]='J';Label1[9]= 'u';Label1[10]='n';break;
             case 0x07:Label1[8]='J';Label1[9]= 'u';Label1[10]='l';break;
             case 0x08:Label1[8]='A';Label1[9]= 'g';Label1[10]='o';break;
             case 0x09:Label1[8]='S';Label1[9]= 'e';Label1[10]='p';break;
             case 0x10:Label1[8]='O';Label1[9]= 'c';Label1[10]='t';break;
             case 0x11:Label1[8]='N';Label1[9]= 'o';Label1[10]='v';break;
             case 0x12:Label1[8]='D';Label1[9]= 'i';Label1[10]='c';break;
            }
            LCD_Sprint(0x80,&Label1);
    }
}