#include <lpc214x.h>

#define NUMBER "9876543210" // Here insert your number where you want to send message

void ser_init(void);
void tx(unsigned char c);
unsigned char rx(void);
void tx_str(unsigned char *s);

// Function to send SMS using the GSM module
void GSM_SendSMS(unsigned char *num1, unsigned char *msg);

void gsm_delay(void);
unsigned int dell;

int callingGSM_from_mainModule()
{
    ser_init();
    GSM_SendSMS(NUMBER, "Welcome to the Our Project!");
    while (1)
        ;
}

void GSM_SendSMS(unsigned char *num1, unsigned char *msg)
{
    tx_str("AT");
    tx(0x0d);

    gsm_delay();

    tx_str("AT+CMGF=1");
    tx(0x0d);

    gsm_delay();

    tx_str("AT+CMGS=");
    tx('"');

    while (*num1)
        tx(*num1++);
    tx('"');
    tx(0x0d);

    gsm_delay();

    while (*msg)
        tx(*msg++);
    tx(0x1a);

    gsm_delay();
}

void gsm_delay()
{
    unsigned long int gsm_del, ff;
    for (gsm_del = 0; gsm_del <= 500000; gsm_del++)
        for (ff = 0; ff < 25; ff++)
            ;
}

void ser_init()
{
    VPBDIV = 0x02; // PCLK = 30MHz
    PINSEL0 = 0x5;
    U0LCR = 0x83;
    U0DLL = 195;
    U0DLM = 0;
    U0LCR = 0x03;
    U0TER = (1 << 7);
}

void tx(unsigned char c)
{
    U0THR = c;
    while ((U0LSR & (1 << 5)) == 0)
        ;
}

void tx_str(unsigned char *s)
{
    while (*s)
    {
        tx(*s++);
    }
}

unsigned char rx()
{
    while ((U0LSR & (1 << 0)) == 0)
        ;
    return U0RBR;
}
