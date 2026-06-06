#define Teclado_Out PORTB  //Puerto nibble bajo, Filas
#define Teclado_In  PORTB  //Lectura de columnas y filas "CF"
#define Teclado_Dir TRISB  //Configuración del puerto, nibble bajo como salida (Filas)
                           //bibble alto como entrada (Columnas)

void Teclado_Ini();               //Configuración de Puerto p/Teclado
unsigned char Tecla_Presionada(); //Prototipado de la función Teclado