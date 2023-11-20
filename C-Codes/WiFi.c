#include <lpc214x.h>
#include <stdio.h>
#include <string.h>

//void delay(unsigned int count) {
//    unsigned int i;
//    for (i = 0; i < count; i++) {
//        for (int j = 0; j < 1000; j++) {
            // Delay loop
//        }
//    }
//}

void UART0_Init() {
    // Configure UART0 with baud rate 115200, 8 data bits, 1 stop bit, no parity
    U0LCR = 0x83;  // 8 bits, no parity, 1 stop bit, DLAB = 1
    U0DLL = 97;    // Set baud rate to 115200
    U0LCR = 0x03;  // DLAB = 0
}

void UART0_SendChar(char ch) {
    while (!(U0LSR & 0x20));  // Wait until the transmit buffer is empty
    U0THR = ch;               // Send the character
}

//void UART0_SendString(const char *str) {
//    while (*str) {
 //       UART0_SendChar(*str++);
  //  }
//}

char *sendJson(float accX, float accY, float accZ, float gyX, float gyY, float gyZ, float vib, float temp, int accident) {
    PINSEL0 = 0x00000005;  // Configure UART0 pins
    UART0_Init();

    // Initialize ESP8266
    UART0_SendString("AT\r\n");
    delay(1000); // Wait for the ESP8266 to respond
    UART0_SendString("AT+CWJAP=\"vivo-1906\",\"Siddhesh@5449\"\r\n"); // Connect to your Wi-Fi
    delay(5000); // Wait for the ESP8266 to connect to Wi-Fi

    // JSON data
    char json_data[128]; // Make sure the array is large enough to hold your JSON data
	snprintf(json_data, sizeof(json_data), "Bois");
    //snprintf(json_data, sizeof(json_data), "{\"accX\":\"%f\",
//\"accY\":\"%f\",
  //      \"accZ\":\"%f\",
    //    \"gyX\":\"%f\",
      //  \"gyY\":\"%f\",
       // \"gyZ\":\"%f\",
        //\"temp\":\"%f\",
        //\"vib\":\"%f\",
        //\"accident\":\"%d\",
    //}", accX, accY, accZ, gyX, gyY, gyZ, temp, vib, accident);
    
    // Send JSON data to a server
    UART0_SendString("AT+CIPSTART=\"TCP\",\"your_server_ip\",your_server_port\r\n");
    delay(2000);
    UART0_SendString("AT+CIPSEND=");
    UART0_SendChar(strlen(json_data) + 2);
    UART0_SendString("\r\n");
    delay(1000);
    UART0_SendString(json_data);
    delay(2000);
    UART0_SendString("AT+CIPCLOSE\r\n"); // Close the connection

    return 0;
}