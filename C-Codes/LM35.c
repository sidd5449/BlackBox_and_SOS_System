// Temperature reading using LM35

float ReadTemperature() {
    // Set up the ADC for the LM35 sensor
    // Assuming you're using AD0 (P0.23) for the LM35 sensor
    // Make sure to configure the ADC pins and settings as needed

    // Start the conversion
    AD0CR = (1 << 0) | (1 << 21);

    // Wait for the conversion to complete
    while (!(AD0GDR & (1 << 31)))
    {
        // Wait for conversion
    }

    // Read the ADC value
    uint16_t adcValue = (AD0GDR >> 4) & 0xFFF;

    // Convert ADC value to temperature in Celsius
    float temperature = (adcValue * 3300.0 / 4095.0) / 10.0;

    return temperature;
}