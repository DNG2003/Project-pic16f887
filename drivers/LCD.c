#include"LCD.h"

unsigned char DB;
//unsigned char Tecla_Anterior=16;  // inicializo con que ninguna tecla es precionada

void Int_LCD(void)
{
//------------------------configuracion-----------------------------------------
//****************CONDICION INICIAL EN EL PUERTO PARA EL LCD********

   ANSEL=0;                     /* se configura el puerto E como digital
                                 y el TRIS E ,esta configurado como entrada*/
   PORTE&=(0<<RS|0<<RW|0<<E);   // operacion a nivel de bits una (AND )con el
   PORTD=0x30;
                                //  puerto Ese le manda al puerto D = 0011 0000  lo pide la hoja de datos (funtion set )
// luego configuramos
   TRISE&=(0<<RS|0<<RW|0<<E);   // operacion a nivel de bits una (AND ) al trisE
                                // y lo fuerza que sea cero por lo que se
                                // configura como salidael puerto E
   TRISD=0;                     // se configura el puerto D como salida


//------------------------RESET_LCD---------------------------------------------
//************* RESET DE LA LCD***********************
   //funcion de reset
   //tiempo de inicializacion interna del modulo dle LCD

  delay_ms(50);
//----------------------CONFIG_SET----------------------------------------------
/**************CONFIGURACION DEL LCD***********
 RS RW DB7 DB6 DB5 DB4 DB3 DB2 DB1 DB0
 0  0   0   0   1   1  NL   F   X  X
 NL=0 modo de 1 linea      F=0 matriz de 5x7 pixeles
 NL=1 modo de 2 linea      F=1 matriz de 5x10 pixeles
 */
 DB=(1<<DB5)|(1<<DB4)|(1<<NL)|(0<<F);

 LCD_Enable(DB);
//--------------------DISPLAY_ON_OFF--------------------------------------------
  /**************DISPLAY ON/OFF control***********
 RS RW DB7 DB6 DB5 DB4 DB3 DB2 DB1 DB0
 0  0   0   0   1   1  1   DSP   CUR  BLK

DSP=0 Display off     CUR=0 Curso off      BLK=0 blink off
DSP=1 Display on      CUR=1 Curso on       BLK=1 blink on

*/

  DB=(1<<DB3)|(1<<DSP)|(0<<CUR)|(0<<BLK);

  LCD_Enable(DB);
//----------------------ENTRY_MODE_SET------------------------------------------
 /**************Entry Mode Set***********
 RS RW DB7 DB6 DB5 DB4 DB3 DB2 DB1 DB0
 0  0   0   0   0   0  0   1   ID  SH

 ID=0 Decremento mode     SH=0 entre shiff off
 ID=1 incremento mode     SH=1 entre shiff on
 */
   DB=(1<<DB2)|(1<<ID)|(0<<SH);
   LCD_Enable(DB);
}
//--------------------DISPLAY_ON_OFF--------------------------------------------
void DISPLAY_ON_OFF(unsigned char Y)
{
/**************DISPLAY ON/OFF control***********
 RS RW DB7 DB6 DB5 DB4 DB3 DB2 DB1 DB0
 0  0   0   0   1   1  1   DSP   CUR  BLK

DSP=0 Display off     CUR=0 Curso off      BLK=0 blink off
DSP=1 Display on      CUR=1 Curso on       BLK=1 blink on

*/

  DB=(1<<DB3)|(1<<DSP)|(0<<CUR)|(Y<<BLK);

  LCD_Enable(DB);
}
void LCD_Entry_Mode_Set(unsigned char ID_Mode,unsigned char shift)
{
    /**************Entry Mode Set***********
 RS RW DB7 DB6 DB5 DB4 DB3 DB2 DB1 DB0
 0  0   0   0   0   0  0   1   ID  SH

 ID=0 Decremento mode     SH=0 entre shiff off
 ID=1 incremento mode     SH=1 entre shiff on
 */
   DB=(1<<DB2)|(ID_Mode<<ID)|(shift<<SH);
   LCD_Enable(DB);

}

void CLEAR_DISPLAY(void)
{
    /************** Clear DISPLAY***********
 RS RW DB7 DB6 DB5 DB4 DB3 DB2 DB1 DB0
 0  0   0   0   0   0  0   0   0  1
*/
  DB=0x01;      // limpia el display completo y colocara
                // la direccion 0 en la DDRAM
  LCD_Enable(DB);
}
void LCD_SET_DDRAM(char x)
{
 /**************Direccion RAM***********
 RS RW DB7 DB6 DB5 DB4 DB3 DB2 DB1 DB0
 0  0   1   1   0   0  0   0   0  0
*/
    //DB=0XC0;  // D7-->1 y D6 a D0  va la direccion que quieras acceder DDRAM
    DB=x;
    LCD_Enable(DB);
}

void LCD_Enable(unsigned char DB)
{
  // señal de habilitacion

  PORTD=DB;                // manda lo que tiene el registro DB al PORTD
  PORTE|=(1<<E);  // se hace una operacion a nivel de bit una  OR con el puerto E con el E(enable) lo manda a 1 lo que lo habilita
  delay_ms(2);
  PORTE&=(~(1<<E)); // se hace una operacion a nivel de bits una AND con el puerto E con el E(enable) con una not
                    // lo invierte ahora se deshabilita

}

/**************FUNCION DONDE DESCOMPONE EL NUMERO******************************/

void Mostrar_LCD(char Dec,char Uni,char Deci)
{
  PORTE|=(1<<RS);

  DB=Dec+48;
  LCD_Enable(DB);

  DB=Uni+48;
  LCD_Enable(DB);

  //DB=46;
  //LCD_Enable(DB);

  //DB=Deci+48;
 // LCD_Enable(DB);
 
  DB=223;
  LCD_Enable(DB);
  
  DB=67;
  LCD_Enable(DB);

  PORTE&=~((1<<RS));
}

//********FUNCIONES PARA LA CREACION DE UNA ANIMACION***************************
void SET_CGRAM_POSICION_CARACTER(char z)
{
     // para acceder al comando de la CGRAM DB6-->1
     // mas la direccion donde lo queremos aguardar(DB5-DB0)
  DB=0;
  DB=((1<<DB6)|z);
  LCD_Enable(DB);      // mandamos un pulso y ya estamos dentro
  DB=0; // por ahorita lo limpiamos
}

void SET_CGRAM_CARACTER(char y[])
{
  /**************CGRAM***********
    ponernos en modo de dato RS-->1
    DB5 a DB0 Guardar el caracter que deceamos crear */
 unsigned char i=0;
 PORTE|=(1<<RS); //modo datos

 while((i<=7))
  {
     DB=y[i];        // toma un caracter del arreglo
     LCD_Enable(DB);            //Deposita el caracter en el puerto y lo envia al LCD
     i++;                 // incrementa el indice del arreglo
  }
  PORTE&=~((1<<RS));  // se desactiva el modo datos sin alteral otro valor
  DB=0; // por ahorita lo limpiamos

}

void SET_CGRAM_POSICION_A_DDRAM_CARACTER(char w ,char v) // posicion donde nos queremos dirigir(donde queremos cologar el caracter el la DDRAM)
{
     DB|=((1<<DB7)|w); // W  seral la posicion donde queremos dejar el caracter (de la DDRAM)

     LCD_Enable(DB);  // ya esta en la posicion donde queremos mostrar el caracter
     // en seguida poner en modo datos RS-->1
     PORTE|=(1<<RS); // nos ponemos de nuevo en modo datos
     // debemos de mandar la direccion donde esta aguardado el caracter
     DB=0;
     DB=v;// v sera la direccion de memoria donde se aguardo el caracter
     LCD_Enable(DB);
     PORTE&=~((1<<RS)); // opcional a menos que quieras seguir mandando el mismo caracter y cambio  de direction

}
/*******FIN DE LA CREACION DE LA ANIMACION*************************************/

/**********FUNCION_PARA_TECLADO_MATRIZ*****************************************/
/*unsigned char LCD_Char(unsigned char TP)
{

         if(TP!=16)  //significa que no se teclea nada
         {
            if(TP!=Tecla_Anterior)
            {
                // LCD_Write(TP);  //aqui escribe cuando se presiona la tp
            }
         }
         tecla_anterior = TP; // Actualiza la tecla anterior
}
 */

/**************FUNCION_PARA_PARA_ESCRIBIR_EN_LA_LCD****************************/
void LCD_Write(unsigned char dataram)  // escritura en el bus
{
   // escritura a CGRAM o DDRAM
        DB=dataram;
        PORTE|=(1<<RS);
        LCD_Enable(DB);
        PORTE&=~((1<<RS));
}
/***************FUNCION_PARA_MOSTRAR_ARRAY*************************************/
void LCD_Sprint(unsigned char DDaddr,unsigned char *String_Buffer) //las array se quedaran en la memoria ram
{
    //Imprimir cadena de texto
    LCD_SET_DDRAM(DDaddr);
    //Ubicacion en pantalla
    while((*String_Buffer!='\n'))
    {
     LCD_Write(*(String_Buffer++));
    }
}

void LCD_Sprint_Const(unsigned char DDaddr,const char *String) // las array se quedaran en la memoria flah
{
 unsigned char j=0;
    //Imprimir cadena de texto
    LCD_SET_DDRAM(DDaddr);
    //Ubicacion en pantalla

    for(j=0;String[j]!='\n'; j++)
    {
        LCD_Write(String[j]);
    }

}

void LCD_BCD_print(unsigned char DDaddr,unsigned int value)
{
     //Imprimir valor BCD Empacado en ASCII

     unsigned char NBUFFER[3]={'0','0','\n'};
     unsigned char z;
     LCD_Set_DDRAM(DDaddr);                   //Ubicacion en pantalla

     //Desempacar BCD
     NBUFFER[0]+=(value&0xF0)>>4;             //BCD Decenas
     NBUFFER[1]+=(value&0x0F);                //BCD Unidades

     for(z=0;(NBUFFER[z]!='\n');z++)
     {
       LCD_Write(NBUFFER[z]);
     }

}

unsigned char ASCII_A_Hex_Num(unsigned char ascii_hex) {
    if (ascii_hex >= '0' && ascii_hex <= '9') {
        return(ascii_hex -'0'); // Restar el valor ASCII de '0' para obtener el valor numerico (0-9)
    } else {}
}