/*********************VARIABLES_I2C_Ds1307*************************************/
void I2C_Ds1307R(void);    //Lectura con 12C en Ds1307
extern char Label1[];
extern char Seg,Min,Hour,Day,Date,Month,Year,TDay;
void Mostrar_lcd_DS1307();
void I2C_Ds1307W(void);    //Escritura con 12C en Ds1307

