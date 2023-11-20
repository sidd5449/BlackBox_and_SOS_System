#include <lpc214x.h>
void delay(unsigned int count) {
    unsigned int i;
    for (i = 0; i < count; i++) {
        for (int j = 0; j < 1000; j++) {
            // Delay loop
        }
    }
}

void UART1_Init_1() {
    // Configure UART0 with baud rate 9600, 8 data bits, 1 stop bit, no parity
    U1LCR = 0x83;  // 8 bits, no parity, 1 stop bit, DLAB = 1
    U1DLL = 97;    // Set baud rate to 9600
    U1LCR = 0x03;  // DLAB = 0
}

char UART1_ReadChar() {
    while (!(U1LSR & 0x01));  // Wait until receive data is available
    return U1RBR;             // Return received character
}

void UART1_SendChar(char ch) {
    while (!(U1LSR & 0x20));  // Wait until the transmit buffer is empty
    U1THR = ch;               // Send the character
}

void UART1_SendString(const char *str) {
    while (*str) {
        UART1_SendChar(*str++);
    }
}

char *getGPS() {
    char gps_data[128]; // Make sure the array is large enough to hold GPS data
    char *gpgga_prefix = "$GPGGA,";

    PINSEL1 = 0x00000005;  // Configure UART0 pins
    UART1_Init_1();

    while (1) {
        char received_char = UART1_ReadChar();
        if (received_char == '$') {
            // Start of a new NMEA sentence
            memset(gps_data, 0, sizeof(gps_data));
            gps_data[0] = '$';
            gps_data[1] = received_char;
            int i = 2;

            while (1) {
                received_char = UART1_ReadChar();
                gps_data[i++] = received_char;

                // Check if the NMEA sentence is complete
                if (i >= 7 && strncmp(gps_data + i - 7, "\r\n", 2) == 0) {
                    gps_data[i] = '\0';
                    break;
                }
            }

            // Check if it's a GPGGA sentence
            if (strncmp(gps_data, gpgga_prefix, strlen(gpgga_prefix)) == 0) {
                // Parse the GPGGA sentence for GPS coordinates
                // Extract latitude, longitude, and other relevant information
                // For example:
                char latitude[12];
                char longitude[12];
                if (sscanf(gps_data, "$GPGGA,%*d.%*d,%10[^,],%*c,%11[^,],", latitude, longitude) == 2) {
                    // latitude and longitude contain the GPS coordinates
                    // You can use these values as needed
                }
            }
        }
    }

    return gps_data;
}
