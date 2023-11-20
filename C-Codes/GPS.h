#ifndef getGPS_ /* Include guard */
#define getGPS_

void delay(unsigned int count);
void UART1_Init();
char UART1_ReadChar();
void UART1_SendChar(char ch);
void UART1_SendString(const char *str);
char *getGPS();
/* An example function declaration */

#endif // FOO_H_