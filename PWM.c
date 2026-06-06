#include"PWM.h"
#include "LM75.h"
/**************************FUNCIONES DE PWM ***********************************/

void PWM_CFG()
{
    CCP1CON.P1M1 = 0;
    CCP1CON.P1M0 = 0;
    CCP1CON.CCP1M3 = 1;
    CCP1CON.CCP1M2 = 1;

    PIR1.TMR2IF = 0;
    T2CON.TMR2ON = 1;
    TRISC.RC2 = 0;
}

void Ancho_Pulso(int ancho){
    CCP1CON |= ((ancho&0x0003)<<4);
    CCPR1L = ancho >> 2;
}

void Periodo(int t_useg){
    PR2 =(t_useg - 1);
}

void Confg_PWM()                           // la resolucion del pwm es de 0 a 1023 bit
{

   if(temperature<=25){Ancho_Pulso(0);}   // Ancho_Pulso= 0/1023--> 0% de su ciclo de trabajo
    else if(temperature >= 26 && temperature <=30){Ancho_Pulso(333);} // Ancho_Pulso= 333/1023--> aprox 33% de su ciclo de trabajo
    else if(temperature>=31 && temperature <=35){Ancho_Pulso(666);}  // Ancho_Pulso= 666/1023--> aprox 65% de su ciclo de trabajo
    else{Ancho_Pulso(999);}                                          // Ancho_Pulso= 999/1023--> aprox 97% de su ciclo de trabajo

}