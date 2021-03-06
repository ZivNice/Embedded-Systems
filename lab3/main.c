#include "msp.h"
#include "uart.h"
#include "circbuf.h"
#include "processing.h"
#include <stdio.h>
#include "eScooter.h"


CircBuf_t * TXBuf;
CircBuf_t * RXBuf;

#define EXTRACREDIT

uint8_t work = 0; //Flag bit. Is one if I want to process info
uint8_t transmit = 0; //Flag bit. is one if I want to send the RXBuf
uint8_t updateDistance = 0; //Flag Bit. Is one if we transmit eScooter distance
uint32_t alp = 0; //Number of alphabetical chars
uint32_t pun = 0; //Number of punctuation chars
uint32_t num = 0; //Number of numerical chars
uint32_t whi = 0; //Number of white chars
uint32_t ran = 0; //Number of random chars
uint32_t systickCounter = 0; //Count how many time SysTick counts down


uint8_t  currentChar = 0;


/**
 * main.c
 */
void main(void)
{
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;     // stop watchdog timer

    TXBuf = createCircBuf(256);
    RXBuf = createCircBuf(256);

    if(!TXBuf || !RXBuf){
        return;
    }

    volatile uint8_t i;

#ifdef TESTCIRCBUF
    for(i=1; i<7; i++){
        addItemCircBuf(TXBuf, i);
    }
    uint8_t pop = removeItem(TXBuf);
    addItemCircBuf(TXBuf, 10);
#endif
    __enable_irq();
    configure_clocks();
    configure_serial_port();
    configurePorts();
#ifdef ESCOOT
    configure_eScooter();
#endif


#ifdef  UART_TESTS
    uint8_t ptr[] = { 0xAA,'J'};
#endif

#ifdef  BLOCKING
    uint8_t sentence[] = "Why not Zoidberg?";
    UART_send_n(sentence, 18);
#endif

#ifdef   INTERRUPT_TEST
    for(i =0; i < 18; i++){
        addItemCircBuf(TXBuf, sentence[i]);
    }
    UART_send_byte(removeItem(TXBuf));
#endif

#ifdef EXTRACREDIT
    SysTick->LOAD = 1210250;   // Give SysTick a starting value to count down from
    SysTick->CTRL = BIT0 | BIT1 | BIT2;  // Enable SysTick
#endif

while(1){
#ifdef  UART_TESTS
      UART_send_n(ptr, 1);
#endif

#ifdef DEMO
      if(work){
          work = 0;
          analyzeBuf();
      }
      if(transmit==1){
          transmit = 0;
          transmitRX();
      }
#endif

#ifdef ESCOOT
      if(updateDistance){
          updateDistance = 0;
          transmitDistance();
      }

#endif

#ifdef EXTRACREDIT
      if(work){
          work = 0;
          analyzeChrEC(currentChar);
      }
      if(transmit){
          transmit = 0;
          transmitEC();
      }
#endif

    }
}
