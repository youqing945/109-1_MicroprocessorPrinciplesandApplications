/*
 * File:   motor.c
 * Author: chen yu an
 *
 * Created on 2021年1月9日, 下午 4:21
 */

#include <xc.h>
#include <pic18f4520.h>

#pragma config OSC = INTIO67 // Oscillator Selection bits
#pragma config WDT = OFF     // Watchdog Timer Enable bit 
#pragma config PWRT = OFF    // Power-up Enable bit
#pragma config BOREN = ON   // Brown-out Reset Enable bit
#pragma config PBADEN = OFF     // Watchdog Timer Enable bit 
#pragma config LVP = OFF     // Low Voltage (single -supply) In-Circute Serial Pragramming Enable bit
#pragma config CPD = OFF     // Data EEPROM　Memory Code Protection bit (Data EEPROM code protection off)

void main(void) {
    // 設定TIMER2, prescaler為4
    T2CON = 0b01111101;
    // 設定OSC頻率，Fosc為125k = Tosc為8µs
    OSCCONbits.IRCF = 0b001;
    // 設定CCP1
    CCP1CONbits.CCP1M = 0b1100;
    // 設定CCP2
    CCP2CONbits.CCP2M = 0b1100;
    // 將RC1設定為輸出，並初始化(因為CCP2和RC1是同一個port)
    TRISC = 0;
    LATC = 0;
    TRISE = 0xF;
    int mode = LATE;
 
    // 設定pr2和ccp的數字來調整輸出的PWM週期和Duty Cycle(高電位時間，訊號越大增加電壓) Tosc是石英震盪器的頻率
    // period = (PR2+1)*4*Tosc*(TMR2 prescaler) = (0x9b + 1) * 4 * 8µs * 4 = 0.019968s ~= 20ms
    PR2 = 0x9b;
    // duty cycle = (CCPR1L:CCP1CON<5:4>)*Tosc*(TMR2 prescaler) = (0x0b*4 + 0b01) * 8µs * 4 = 0.00144s ~= 1450µs
    //duty=500=0x03
    //duty=2400=CCPR1L=0x12
    CCPR1L = 0x14;//CCPRxH才是真正用到的，但使用時會設定在CCPRxL等周期結束後會自動將CCPRxL存至CCPRxH
    CCP1CONbits.DC1B = 0b11;  
    
    CCPR2L = 0x03;//CCPRxH才是真正用到的，但使用時會設定在CCPRxL等周期結束後會自動將CCPRxL存至CCPRxH
    CCP2CONbits.DC2B = 0b11;  
    
    while(1){
        while( CCPR2L < 0x14){
            for(int i =0;i<mode*50;++i){
            }
            ++CCPR2L;
            --CCPR1L;
        }
        while( CCPR2L > 0x03){
            for(int i =0;i<mode*50;++i){
            }
            --CCPR2L;
            ++CCPR1L;
        }
    }
    return;
}


