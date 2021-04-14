/*
 * File:   buzzer.c
 * Author: chen yu an
 *
 * Created on 2021年1月9日, 上午 9:57
 */
#include <xc.h>
#include <pic18f4520.h>

#define _XTAL_FREQ      4000000
#define TMR2PRESCALE    16

// CONFIG1
#pragma config OSC = INTIO67    // Oscillator Selection bits
#pragma config WDT = OFF        // Watchdog Timer Enable bit 
#pragma config PWRT = OFF       // Power-up Enable bit
#pragma config BOREN = ON       // Brown-out Reset Enable bit
#pragma config PBADEN = OFF     // Watchdog Timer Enable bit 
#pragma config LVP = OFF        // Low Voltage (single -supply) In-Circute Serial Pragramming Enable bit
#pragma config CPD = OFF        // Data EEPROM　Memory Code Protection bit (Data EEPROM code protection off)
// CONFIG2
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal External Switchover mode disabled)

// TONES  ==========================================
#define  c     261
#define  d     293
#define  e     329
#define  f     349
#define  g     392
#define  a     440
#define  b     493
#define  C     523
#define  D     587
#define  E     659
#define  F     698
#define  G     784
#define  A     880
// Define a special note, 'R', to represent a rest
#define  R     0
// ==================================================

int tempo = 2000;

int current_tone = 0; //current playing note
int current_tone_duration = 0; //current note duration

void delay_ms(unsigned int milliseconds) {
   while(milliseconds > 0) {
      milliseconds--;
       __delay_us(990);
   }
}

void SetupClock() {
    OSCCONbits.IRCF = 0b110; //set internal oscillator to 4 Mhz
}

void PWM1_Init(long desired_frequency) {
    PR2 = (_XTAL_FREQ / (desired_frequency * 4 * TMR2PRESCALE)) - 1;
    current_tone = desired_frequency;
}

int PWM_Max_Duty() {
    return (_XTAL_FREQ / (current_tone * TMR2PRESCALE));
}

void PWM1_Duty(unsigned int duty) {
    if (duty < 1024) {
        duty = ((float) duty / 1023) * PWM_Max_Duty();
        CCP1X = duty & 2;
        CCP1Y = duty & 1;
        CCPR1L = duty >> 2;
    }
}

void PWM1_Mode_On() {
    // 設定CCP1
    CCP1CONbits.CCP1M = 0b1100;
}

void PWM1_Start() {
    PWM1_Mode_On();

#if TMR2PRESCALE == 1
    T2CKPS0 = 0;
    T2CKPS1 = 0;
#elif TMR2PRESCALE == 4
    T2CKPS0 = 1;
    T2CKPS1 = 0;
#elif TMR2PRESCALE == 16
    T2CKPS0 = 1;
    T2CKPS1 = 1;
#endif
    TMR2ON = 1;
}

void PWM1_Stop() {
    CCP1M3 = 0;
    CCP1M2 = 0;
}

void playTone() {
    PWM1_Init(current_tone);
    PWM1_Duty(511);
        
    delay_ms(current_tone_duration);
    PWM1_Duty(0);
}
int main(int argc, char** argv) {
    short melody0[] = {g, g, g, E, D, C, g, R, g, g, g, E, D, C, a, R, a, a, a, F, E, D, b, R, R, G, G, F, D, E, C,
                      g, E, D, C, g, R, g, g, g, E, D, C, a, R, a, a, a, F, E, D, G, G, G, A, G, F, D, C, G,
                      E, E, E, E, E, E, E, G, C, D, E, R, R, F, F, F, F, E, E, E, D, D, E, D, G,
                      E, E, E, E, E, E, E, G, C, D, E, R, R, F, F, F, F, E, E, G, G, F, D, C, R  };
    char beats0[] =   {8, 8, 4, 4, 4, 4, 2, 4, 8, 8, 4, 4, 4, 4, 2, 4, 8, 8, 4, 4, 4, 4, 2, 4, 4, 4, 4, 4, 4, 2, 2,
                      4, 4, 4, 4, 2, 4, 8, 8, 4, 4, 4, 4, 2, 4, 8, 8, 4, 4, 4, 4, 4, 4, 2, 4, 4, 4, 4, 2, 2,
                      4, 4, 2, 4, 4, 2, 4, 4, 4, 4, 2, 4, 4, 4, 4, 2, 4, 4, 2, 4, 4, 4, 4, 2, 2,
                      4, 4, 2, 4, 4, 2, 4, 4, 4, 4, 2, 4, 4, 4, 4, 2, 4, 4, 2, 4, 4, 4, 4, 2, 2  };
   
    short melody1[] = {g,C,C,D,C,b,a,a,a,D,D,E,D,C,b,g,g,E,E,F,E,D,C,a,g,g,a,D,b,C,g,C,C,C,b,b,C,b,a,g,D,E,D,C,G,g,g,g,a,D,b,C};
    char beats1[] =   {4,4,8,8,8,8,4,4,4,4,8,8,8,8,4,4,4,4,8,8,8,8,4,4,8,8,4,4,4,2,4,4,4,4,2,4,4,4,4,2,4,4,4,4,4,4,8,8,4,4,4,2};
    char MELODY_LENGTH0 = sizeof (melody0) / sizeof (melody0[0]);
    char MELODY_LENGTH1 = sizeof (melody1) / sizeof (melody1[0]);
    SetupClock();
    TRISCbits.TRISC2 = 0; // 將RC2設定為輸出，並初始化(因為CCP1和RC2是同一個port)
    PORTC = 0x00;
    TRISE = 0xF;
    int mode = LATE;
    
    INTCON2=0x00;
    RCONbits.IPEN = 1;
    INTCONbits.GIE = 1;
    INTCONbits.INT0IE = 1;        

    PWM1_Init(500); //exact value doesn't matter at all, just not 0
    PWM1_Duty(0);
    PWM1_Start();

    while (1) {
        if(mode<4){
            for (int i = 0; i < MELODY_LENGTH0; i++) {
                current_tone = melody0[i];
                current_tone_duration = tempo / beats0[i];
                playTone();
                delay_ms(tempo/200);
                mode = LATE;
                if(mode>4){
                    break;
                }
            }
            __delay_ms(2000);
        }
        else{
            for (int i = 0; i < MELODY_LENGTH1; i++) {
                current_tone = melody1[i];
                current_tone_duration = tempo / beats1[i];
                playTone();
                delay_ms(tempo/200);
                mode = LATE;
                if(mode<=4){
                    break;
                }
            }
            __delay_ms(2000);
        }
    }
    return 0;
}