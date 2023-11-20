volatile char gsm_rx_buffer[256]; // Circular buffer for GSM data
volatile char gps_rx_buffer[256]; // Circular buffer for GPS data

// GSM data processing task
void GSM_ProcessDataTask()
{
    while (1)
    {
        // Check the GSM circular buffer for incoming data
        // Parse and process GSM data
        // Implement appropriate logic
    }
}

// GPS data processing task
void GPS_ProcessDataTask()
{
    while (1)
    {
        // Check the GPS circular buffer for incoming data
        // Parse and process GPS data
        // Implement appropriate logic
    }
}

// UART interrupt handler for GSM
void GSM_UART_InterruptHandler()
{
    // Receive and store incoming GSM data in the GSM buffer
    // Signal the GSM processing task to start processing
}

// UART interrupt handler for GPS
void GPS_UART_InterruptHandler()
{
    // Receive and store incoming GPS data in the GPS buffer
    // Signal the GPS processing task to start processing
}