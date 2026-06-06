#define   DB0          0      //bit cero del data bus

#define   DB1          1      //bit uno  del data bus

#define   DB2          2      //bit dos  del data bus

#define   DB3          3      //bit tres del data bus

#define   DB4          4      //bit cuatro  del data bus

#define   DB5          5      //bit cinco del data bus

#define   DB6          6      //bit seis del data bus

#define   DB7          7      //bit  siete del data bus

 //----------------------------------------------------------------------------

#define   ID          1      //incremento/decremento mode  --> las direcciones

#define   SH          0      //entere shift ON/OFF    --> desplazamientos

#define   BLK         0      //blink ON/OFF    --> parpadeo en el cursor

#define   CUR         1      //cursor ON/OFF  -->mustra una barrita arriba

#define   DSP         2      //Display 0N/OFF

#define   F           2      //Matrix

#define   NL          3      // N lineas

#define  B_Busy       7     // Bits busy Flag

#define  RS           0     // bit select register del LCD

#define  RW           1     // bit read/write del LCD

#define  E            2     //bit enable

#define  SC           3     //Desplazamiento del Display/cursor

#define  RL             2      //Izquierda/derecha



/**************************CONFIGURACION DE TERMINALES*********************
|1  |2  |3  |4  |5  |6  |7  |8  |9  |10  |11  |12  |13  |14 | modulo de LCD
GND VCC  V0  RS  RW  E  DB0  DB1   DB2  DB3 DB4  DB5  DB6  DB7

               RE0  RE1  RE2  RD0  RD1  RD2  RD3 RD4 RD5 RD6 RD7 terminales del micro
*/

// void configuracion(void);                       //configuracion

//void  RESET_LCD(void);                          // funcion de reset

//void CONFIG_SET(void);                          //configuracion del LCD

void DISPLAY_ON_OFF(unsigned char Y);                      // activacion del LCD

//void ENTRY_MODE_SET(void);                      //movimiento del cursor

void CLEAR_DISPLAY(void);                        //limpiar el display

void LCD_SET_DDRAM(char x);                //direccion de inicio en el LCD

void delay_ms(unsigned int msegs);               //funcion para imprimir cadena

void Int_LCD(void);                            // iniicializacion de la lcd

void Mostrar_LCD( char Dec,char Uni,char Deci);
//***********prototipos de las funciones para la animacion**********************
void SET_CGRAM_POSICION_CARACTER(char z);// para crear caracteres y guardarlos en la CGRAM

void SET_CGRAM_CARACTER(char y[]);

void SET_CGRAM_POSICION_A_DDRAM_CARACTER(char w ,char v);

//prototipado de las funcion para convertir en LCD un caracter del teclado
unsigned char LCD_Char(unsigned char TP);

// escribir en el bus
void LCD_Write(unsigned char dataram);


/*************Prototipado de la funoión en Lod.h*******************************/
//Imprinir cadena de texto

void LCD_Sprint(unsigned char DDaddr,unsigned char*String_Buffer);

void LCD_Enable(unsigned char DB);   // carga datos al bus

/*******Prototipado de la función en Lcd.h*************************************/
//Imprimir valor BCD Empacado en ASCII

void LCD_BCD_print(unsigned char DDaddr,unsigned int value);

unsigned char ASCII_A_Hex_Num(unsigned char ascii_hex);

void LCD_Entry_Mode_Set(unsigned char ID_Mode,unsigned char shift);

void LCD_Sprint_Const(unsigned char DDaddr,const char *String);