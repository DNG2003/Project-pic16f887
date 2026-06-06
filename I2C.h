// laboratorio 14 "I2C Driver"

/*************Asignacion de terminales y puerto********************************/

#define SCL_Dir         TRISC.RC3
#define SDA_Dir         TRISC.RC4
#define SCL             PORTC.RC3
#define SDA             PORTC.RC4

/**********Bits de Configuracion***********************************************/
#define Slave_Mode_10bits_SS     0x0F     //I2C slave Mode, 10 bit addrs + Start + Stop
#define Slave_Mode_7bits_SS      0x0E     //12c slave Mode, 7 bit addrs + Start + Stop
#define Master_Mode_Firmrare     0x0E     //I2C Firmware Controlled Master Mode(Slave Idle)
#define Master_Mode_Clock        0x08     //12C Master Mode, clock definido en SSPADD
#define Slave_Mode_10bits        0x07     //12c slave Mode, 10 bit addrs
#define Slave_Mode_7bits         0x06     //12C slave Mode, 7 bit addrs

//****** Velocidad de I2C******************************************************/
#define FOSC          4000000    //HZ
#define I2C_Speed     100000     //HZ

#define SSPADD_Speed ((FOSC/(4*I2C_Speed))-1) //Velocidad del 12c

/******Direccion del Ds1307***************************************************/

#define   Ds1307_ID    0x68     //Direccion del Ds1307 (DATASHEET)
#define   R             1       //Read
#define   W             0       //Write
#define   Ds1307_R       ((Ds1307_ID<<1) + R) //Lectura del D81307
#define   Ds1307_W       ((Ds1307_ID<<1) + W) //Escritura del D81307

/******Direccion del LM75***************************************************/

#define   LM75_ID    0x48     //Direccion del LM75 (DATASHEET)
#define   LM75_R       ((LM75_ID<<1) + R) //Lectura del LM75
#define   LM75_W       ((LM75_ID<<1) + W) //Escritura del LM75
// I2C_Speed     100000     //HZ su velocidad es de hasta  400khz

/********Acknowledge***********************************************************/

#define ACK      0      //Acknowledge      ACK=0,Recibido
#define NACK     1      //No Acknowledge   ACK=1

void I2C_init(void);
void I2C_port(void);
void I2C_wait(void);
void I2C_start(void);
void I2C_restart(void);
void I2C_stop(void);
void I2C_write(unsigned char Data);
unsigned char I2C_read(unsigned char Ack);