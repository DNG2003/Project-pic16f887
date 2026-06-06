#include"I2C.h"
#include"LCD.h"
#include"Teclado.h"
#include"PWM.h"
#include"LM75.h"
#include"Ds1307.h"
#include"RS232.h"
/***************ARRAYS_PARA_LCD************************************************/

//unsigned char Label1[]={"DATE:  /   /  ~ \n"};
unsigned char Label2[]={"TIME:  :  :    \n"};

const char Label3[]={"1-Conf_Hrs/Date\n"};
const char Label4[]={"2-Most_Temp\n"};

unsigned  char Label5[]={"DATE:  /  /  :  \n"};
unsigned  char Label6[]={"TIME:  :  :    \n"};

const char Label7[]={"TEMPERATURA:\n"};

//unsigned char figura_1[8]={0x0E,0x0E,0X15,0X0E,0X04,0X0A,0X11,0X00};
//unsigned char figura_2[8]={0x0E,0x0E,0X04,0X0E,0X15,0X0A,0X0A,0X00};

/*************PROTOTIPOS_DE_FUNCIONES******************************************/
void Animacion();

void Menu_ini();
void menu();
void Muestra_sub_menu_LCD();

void Confg_Hrs_Date();
void Confg_temp();

/*********VARIABLES_PARA_TECLADO_LCD_TIPO_MENU*********************************/

unsigned char tecla_actual=0,tecla_anterior=16,estado_menu=0,INICIO=0;

/*********VARIABLES_PARA_CONFIG_RELOJ******************************************/

unsigned char Seg1=0,Min1=0,Hour1=0,Day1=0,Date1=0,Month1=0,Year1=0;
unsigned char i=0,Flag=0,ASCII=0,HEX=0,HIGH=0,LOW=0;

/*********VARIABLES_PARA_COMUNICACION_RS232************************************/

unsigned char Leer_EUSART();         //Asigación de un valor equivalente al teclado matricial a los datos recividos desde el PC
unsigned char Vusart=0;              //Valor enviado desde la PC equivalente al teclado matricial.
unsigned char usart=0;               // Valor almacenado cuando tecleamos desde la pc
unsigned char  Dato_disponible=0;    // bandera indica cuando se recibio de la pc
unsigned char Obtener_Entrada();
void Mustreo_temp_pc();
/*%%%%%%%%%%%%%%%%%%%%%CODIGO_PRINCIPAL%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

void main()
{
    EUSART();
    Int_LCD();
    Teclado_Ini();
    I2C_init();           //Configuracion MSSP
    I2C_Ds1307W();
    PWM_CFG();
    Periodo(256);
    Ancho_Pulso(0);
    Menu_ini();
    TRISC.RC0=0;
    while (1)
    {

        menu();
        I2C_Ds1307R();
        I2C_LM75R();
        Mustreo_temp_pc();
    }
}

/****************LLAMADO_DE FUNCIONES******************************************/
void interrupt()
{
 if(PIR1.RCIF)
 {                   //Al presionar una tecla en el PC dispara la interrupción
  usart=RCREG;       //Guardar el valor del registro RCREG en la varaible usart
  //TXREG=usart;
  Dato_disponible=1;

 }                   //El valor del registro es el ASSCI de la tecla presionada
}

void Mustreo_temp_pc()
{   Confg_PWM();
    while(!TXSTA.TRMT);        //Bit de estado del registro de desplazamiento de transmision
    TXREG='T';
    while(!TXSTA.TRMT);
    TXREG='E';
    while(!TXSTA.TRMT);
    TXREG='M';
    while(!TXSTA.TRMT);
    TXREG=':';
    while(!TXSTA.TRMT);
    TXREG=Dec+'0';
    while(!TXSTA.TRMT);
    TXREG=Uni+'0';
    while(!TXSTA.TRMT);
    TXREG='º';
    while(!TXSTA.TRMT);
    TXREG='C';
    while(!TXSTA.TRMT);
    TXREG=' ';



}

//Conversion de variable usart por un valor equivalente al teclado matricial
unsigned char Leer_EUSART()
{
 switch(usart)    // verifica en que caso se presiono la letra
  {
   case 0:return Vusart=16; break; //Sin presionar
   case 0x31:return Vusart='1'; break;  //1
   case 0x32:return Vusart='2'; break;  //2
   case 0x33:return Vusart='3'; break;  //3
   case 0x61:return Vusart='A'; break; //A

   case 0x34:return Vusart='4'; break;  //4
   case 0X35:return Vusart='5'; break;  //5
   case 0x36:return Vusart='6'; break;  //6
   case 0x62:return Vusart='B'; break; //B

   case 0x37:return Vusart='7'; break;  //7
   case 0x38:return  Vusart='8'; break;  //8
   case 0x39:return  Vusart='9'; break;  //9
   case 0x63:return  Vusart='C'; break; //C
   
   case 0x30:return  Vusart='0'; break;  //0
   case 0x64:return  Vusart='D'; break;  //D
   
  }
}

unsigned char Obtener_Entrada()
{
    if (Dato_disponible)
     {
        Dato_disponible = 0;    // Limpiar la bandera
        return(Leer_EUSART());
        
    } else {

        return(Tecla_Presionada());

    }
}


void menu()
{
    tecla_actual = Obtener_Entrada();                             // toma el valor que se detecte en teclado_precionado o de la pc

        if (tecla_actual != 16 && tecla_actual != tecla_anterior)  // verificara si es 16(ya que es cuando no esta precionado )
        {                                                          // y asu vez verificara si hubo cambio de teclado para no tener un rebote

            switch(estado_menu)
            {
                case 0:
                    if (tecla_actual == 'A')               //si se preciono 'A'--> muestra sub menu(las dos opcciones que tengo)
                    {                                      // estado_menu=1--> para que se dirija CASO=1--> para verificar si se presiono '1' 0 '2'
                        estado_menu = 1;
                        INICIO=1;                          // como ya entro al submenu ya no se empalmara los numeros
                        Muestra_sub_menu_LCD();
                    }
                    break;
                case 1:                                   // Submenu de Opciones
                    if (tecla_actual == '1')              // si se presiona '1' -->muestra y se difige ala funcion de configuracion de Hrs/Date
                    {                                     // estado_menu= '2'--> se dirige ala funcion de poder configurar Hrs/Date
                        estado_menu = 2;                  // Configuración de Hora/Fecha
                        CLEAR_DISPLAY();
                        LCD_Sprint(0x80,&Label5);         //"DATE:  /  /  :  \n"
                        LCD_Sprint(0xC0,&Label6);         //"TIME:  :  :    \n"

                    } else if (tecla_actual == '2')       // de lo contrio presiona'2'--> muestra la funcion de temperatura
                    {                                     // estado_menu= '3'--> se dirige ala funcion de lectura de temperatura
                        estado_menu = 3;
                        CLEAR_DISPLAY();
                        LCD_Sprint_Const(0x80,Label7);
                        Flag=1;                   // al precionar'2'-->incrementamos la bandera (Flag)para poder entrar ala funcion temp
                                                 // ya que al salir como no vamos A tener una tecla precionada no podremos actualizar
                        Confg_temp();            // De una cargamos los valores para que nos aparezca en la lcd

                    } else if (tecla_actual == 'B')       // de lo contrario presiona'B'-->regresaremos al menu principal
                    {
                        INICIO=0;                         // como ya entro al submenu ya no se empalmara los numeros
                        estado_menu = 0;                  // Volver al menú principal
                        Menu_ini();                       // donde estado_num=0 y verifica si de nuevo se presiono 'A'
                    }
                    break;
                case 2:                                   //si en el sub_menu presionamos el '1'--> queremos configurar el reloj
                    if (tecla_actual == 'B')              // si se presiono'B' regresamos al menu principal
                    {
                                                          // Volver al submenu de opciones
                        Muestra_sub_menu_LCD();
                    } else                                //De lo contrario entramos a configurar el reloj (precargando  valores)
                    {
                        Confg_Hrs_Date();
                    }
                    break;
                case 3:                                   // Sección de Mostrar Temperatura
                    if (tecla_actual == 'B')               // Volver al submenu de opciones si se presiono la tecla 'b'
                    {
                         Flag=0;                         // como nos vamos a regresar al submenu reiniciamos la bandera de mostrar temp
                        Muestra_sub_menu_LCD();          // precargamos de una el sub menu
                    } else
                    {                                   //si en el sub_menu presionamos el '2'--> queremos observar  temperatura
                       Flag=1;

                       Confg_temp();                     // en este caso hacemos lectura de la visualizacion de temperatura
                    }
                    break;
            }
        }
        else if(inicio==0){Mostrar_lcd_DS1307();}  // como no se precionado nada ,pero queremos que se actulizen los valores de fecha y hora
        if(Flag==1){Confg_temp();}                 // como estamos en la funcion de temperatura seguimos actualizando y mostrando temperatura
        tecla_anterior = tecla_actual;             // para evitar rebotes se aguarda la ultimo que se tecleo
}

 void Menu_ini()
{
    CLEAR_DISPLAY();
    LCD_Sprint(0x80,&Label1); // {"DATE:  /   /  ~ \n"};
    LCD_Sprint(0xC0,&Label2); //  {"TIME:  :  :    \n"};
    //Mostrar_lcd_DS1307();

}

void Muestra_sub_menu_LCD()
{
    CLEAR_DISPLAY();
    estado_menu = 1;
    LCD_Sprint_Const(0x80, Label3);  //"1-Confg_Hrs/Date\n"
    LCD_Sprint_Const(0xC0, Label4);  // "2-Most_Temp\n"
}

void Confg_Hrs_Date()
{
   LCD_Sprint(0x80,&Label5);
    LCD_Sprint(0xC0,&Label6);
        switch (i)
        {
        /**********************CONFIGURACION_DIA*******************************/
           case 0:
                  LCD_SET_DDRAM(0x85);       // primera posicion
                  LCD_Write(tecla_actual);   // escribimos el la lcd lo que se tecleo

                  Label5[5] = tecla_actual;    //aguardamos ese valor tecleado en esa posicion

                  ASCII = Label5[5];          // Cargamor el valor ASCII
                  HEX = ASCII_A_Hex_Num(ASCII); // Convercion a Hexadecimal
                  HIGH = (HEX << 4);           // Cargar parte alta de DATE
                  
                  i = 1;                       // incrementamos para el siguiente valor
                  break;

           case 1:
                  if(tecla_actual=='D')        // en el caso que lo queremos borrar lo anterior  se presiona la tecla d
                  {i=0;LCD_SET_DDRAM(0x85);Label5[5]=0;break;} // y nos posiciona de nuevo en ese numero
                  //ASCII=0;
                  LCD_SET_DDRAM(0x86);             // a menos que no se tecleo lo anterior seguimos escribiendo en la lcd
                  LCD_Write(tecla_actual);
                  Label5[6]=tecla_actual;

                  ASCII=Label5[6];              // Carga el valor ASCII
                  HEX=ASCII_A_Hex_Num(ASCII);   //Convercion a Hexadecimal
                  LOW=HEX;                      //Carga parte baja de DATE
                  Date1=(HIGH|LOW);              //Cargar valor  DATE
                  i=2;

                  break;
        /***********************CONFIGURACION_MES******************************/
           case 2:
                  if(tecla_actual=='D')
                  {i=1;LCD_SET_DDRAM(0x86);Label5[6]=0;break;}
                  //ASCII=0;
                  LCD_SET_DDRAM(0x88);
                  LCD_Write(tecla_actual);
                  Label5[8]=tecla_actual;

                  ASCII=Label5[8];              // Cargamor el valor ASCII
                  HEX=ASCII_A_Hex_Num(ASCII);   //Convercion a Hexadecimal
                  HIGH=(HEX<<4);                //Cargar parte alta de MONTH
                  i=3;
                  break;
                                              //{"DATE:  /  /    \n"};
                                             //{"TIME:  :  :    \n"};
            case 3:
                  if(tecla_actual=='D')
                  {i=2;LCD_SET_DDRAM(0x88);Label5[8]=0;break;}
                  //ASCII=0;
                  LCD_SET_DDRAM(0x89);
                  LCD_Write(tecla_actual);
                  Label5[9]=tecla_actual;

                  ASCII=Label5[9];              // Carga el valor ASCII
                  HEX=ASCII_A_Hex_Num(ASCII);   //Convercion a Hexadecimal
                  LOW=HEX;                      //Carga parte baja de MONTH
                  Month1=(HIGH|LOW);             //Cargar parte valor a MONTH
                  i=4;
                  break;
        /***********************CONFIGURACION_ANIO*****************************/
            case 4:
                  if(tecla_actual=='D')
                  {i=3;LCD_SET_DDRAM(0x89);Label5[9]=0;break;}
                  //ASCII=0;                      // Reiniciamos variable
                  LCD_SET_DDRAM(0x8B);
                  LCD_Write(tecla_actual);
                  Label5[11]=tecla_actual;

                  ASCII=Label5[11];              // Cargamor el valor ASCII
                  HEX=ASCII_A_Hex_Num(ASCII);   //Convercion a Hexadecimal
                  HIGH=(HEX<<4);                //Cargar parte alta de YEAR
                  i=5;
                  break;

            case 5:
                 if(tecla_actual=='D')
                 {i=4;LCD_SET_DDRAM(0x8B);Label5[11]=0;break;}
                  //ASCII=0;
                  LCD_SET_DDRAM(0x8C);
                  LCD_Write(tecla_actual);
                  Label5[12]=tecla_actual;

                  ASCII=Label5[12];              // Carga el valor ASCII
                  HEX=ASCII_A_Hex_Num(ASCII);   //Convercion a Hexadecimal
                  LOW=HEX;                      //Carga parte baja de YEAR
                  Year1=(HIGH|LOW);             //Cargar el valor de  YEAR
                  i=6;
                  break;
        /**************CONFIGURACION_DIA_SEMANA********************************/
            case 6:
                  if(tecla_actual=='D')
                  {i=5;LCD_SET_DDRAM(0x8C);Label5[12]=0;break;}
                  //ASCII=0;                      // Reiniciamos variable
                  LCD_SET_DDRAM(0x8E);
                  LCD_Write(tecla_actual);
                  Label5[14]=tecla_actual;

                  ASCII=Label5[14];              // Cargamor el valor ASCII
                  HEX=ASCII_A_Hex_Num(ASCII);   //Convercion a Hexadecimal
                  HIGH=(HEX<<4);                //Cargar parte alta de Day
                  i=7;
                  break;
           case 7:
                  if(tecla_actual=='D')
                  {i=6;LCD_SET_DDRAM(0x8E);Label5[14]=0;break;}
                  //ASCII=0;
                  LCD_SET_DDRAM(0x8F);
                  LCD_Write(tecla_actual);
                  Label5[15]=tecla_actual;

                  ASCII=Label5[15];              // Carga el valor ASCII
                  HEX=ASCII_A_Hex_Num(ASCII);   //Convercion a Hexadecimal
                  LOW=HEX;                      //Carga parte baja de Day
                  Day1=(HIGH|LOW);             //Cargar el valor de  Day
                  i=8;
                  break;

        /***********CONFIGURACION_HORAS****************************************/
           case 8:
                  if(tecla_actual=='D')
                  {i=7;LCD_SET_DDRAM(0x8F);Label5[15]=0;break;}
                  //ASCII=0;                      // Reiniciamos variable
                  LCD_SET_DDRAM(0xC5);
                  LCD_Write(tecla_actual);
                  Label6[5]=tecla_actual;

                  ASCII=Label6[5];              // Cargamor el valor ASCII
                  HEX=ASCII_A_Hex_Num(ASCII);   //Convercion a Hexadecimal
                  HIGH=(HEX<<4);                //Cargar parte alta de HORAS
                  i=9;
                  break;
           case 9:
                  if(tecla_actual=='D')
                  {i=8;LCD_SET_DDRAM(0xC5);Label6[5]=0;break;}
                  //ASCII=0;
                  LCD_SET_DDRAM(0xC6);
                  LCD_Write(tecla_actual);
                  Label6[6]=tecla_actual;

                  ASCII=Label6[6];              // Carga el valor ASCII
                  HEX=ASCII_A_Hex_Num(ASCII);   //Convercion a Hexadecimal
                  LOW=HEX;                      //Carga parte baja de HORAS
                  Hour1=(HIGH|LOW);             //Cargar el valor de  HORAS
                  i=10;
                  break;
        /***********CONFIGURACION_MINUTOS**************************************/
           case 10:
                  if(tecla_actual=='D')
                  {i=9;LCD_SET_DDRAM(0xC6);Label6[6]=0;break;}
                  //ASCII=0;                      // Reiniciamos variable
                  LCD_SET_DDRAM(0xC8);
                  LCD_Write(tecla_actual);
                  Label6[8]=tecla_actual;

                  ASCII=Label6[8];              // Cargamor el valor ASCII
                  HEX=ASCII_A_Hex_Num(ASCII);   //Convercion a Hexadecimal
                  HIGH=(HEX<<4);                //Cargar parte alta de MINUTOS
                  i=11;
                  break;
           case 11:
                  if(tecla_actual=='D')
                  {i=10;LCD_SET_DDRAM(0xC8);Label6[8]=0;break;}
                  //ASCII=0;
                  LCD_SET_DDRAM(0xC9);
                  LCD_Write(tecla_actual);
                  Label6[9]=tecla_actual;

                  ASCII=Label6[9];              // Carga el valor ASCII
                  HEX=ASCII_A_Hex_Num(ASCII);   //Convercion a Hexadecimal
                  LOW=HEX;                      //Carga parte baja de MINUTOS
                  Min1=(HIGH|LOW);             //Cargar el valor de  MINUTOS
                  i=12;
                  break;
        /***********CONFIGURACION_SEGUNDOS*************************************/
           case 12:
                  if(tecla_actual=='D')
                  {i=11;LCD_SET_DDRAM(0xC9);Label6[9]=0;break;}
                  //ASCII=0;                      // Reiniciamos variable           11 y 12
                  LCD_SET_DDRAM(0xCB);
                  LCD_Write(tecla_actual);
                  Label6[11]=tecla_actual;

                  ASCII=Label6[11];              // Cargamor el valor ASCII
                  HEX=ASCII_A_Hex_Num(ASCII);   //Convercion a Hexadecimal
                  HIGH=(HEX<<4);                //Cargar parte alta de SEGUNDOS
                  i=13;
                  break;
           case 13:
                  if(tecla_actual=='D')
                  {i=12;LCD_SET_DDRAM(0xCB);Label6[11]=0;break;}
                  //ASCII=0;
                  LCD_SET_DDRAM(0xCC);
                  LCD_Write(tecla_actual);
                  Label6[12]=tecla_actual;

                  ASCII=Label6[12];              // Carga el valor ASCII
                  HEX=ASCII_A_Hex_Num(ASCII);   //Convercion a Hexadecimal
                  LOW=HEX;                      //Carga parte baja de SEGUNDOS
                  Seg1=(HIGH|LOW);             //Cargar el valor de  SEGUNDOS
                  i=14;
                  break;
           case 14:
                  if(tecla_actual=='D')
                  {i=13;LCD_SET_DDRAM(0xCC);Label6[12]=0;break;}
                  i=15;
                  break;
           case 15:
                if(Tecla_actual=='C')
                {
                    Seg=Seg1;
                    Min=Min1;
                    Hour=Hour1;
                    Day=Day1;
                    Date=Date1;
                    Month=Month1;
                    Year=Year1;
                    TDay=0;

                    I2C_Ds1307W();          // Cargamos los valores
                    I2C_Ds1307R();
                    Mostrar_lcd_DS1307();
                    estado_menu=1;
                    i=0;
                    ASCII=0;
                    Label5[5]=' ';
                    Label5[6]=' ';
                    Label5[8]=' ';
                    Label5[9]=' ';
                    Label5[11]=' ';
                    Label5[12]=' ';
                    Label5[14]=' ';
                    Label5[15]=' ';

                    Label6[5]=' ';
                    Label6[6]=' ';
                    Label6[8]=' ';
                    Label6[9]=' ';
                    Label6[11]=' ';
                    Label6[12]=' ';
                    CLEAR_DISPLAY();
                    Muestra_sub_menu_LCD();

                 }
                 break;
  }return;
}

void Confg_temp()
{
         LCD_SET_DDRAM(0xC0);
         Descomponer_Num(temperature);
         Mostrar_LCD(Dec,Uni,Deci);
         Confg_PWM();

}