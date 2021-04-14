#include <xc.h>
#include <pic18f4520.h>
#include<stdio.h>
#include "setting_hardaware/setting.h"

#pragma config OSC = INTIO67 // Oscillator Selection bits
#pragma config WDT = OFF     // Watchdog Timer Enable bit 
#pragma config PWRT = OFF    // Power-up Enable bit
#pragma config BOREN = ON   // Brown-out Reset Enable bit
#pragma config PBADEN = OFF     // Watchdog Timer Enable bit 
#pragma config LVP = OFF     // Low Voltage (single -supply) In-Circute Serial Pragramming Enable bit
#pragma config CPD = OFF     // Data EEPROM　Memory Code Protection bit (Data EEPROM code protection off)

#define _XTAL_FREQ 200000
unsigned int x;

#define seg_port LATD
#define zero    0xC0
#define one     0xF9
#define two     0xA4
#define three   0xB0
#define four    0x99
#define five    0x92
#define six     0x82
#define seven   0xF8
#define eight   0x80
#define nine    0x90

int mode = 0;
int lastmode = -1;
void __interrupt(high_priority) ISR(void){
    if(mode<7){
        ++mode;
        __delay_ms(500);
    }
    else{
        mode = 0;
    }
    INTCONbits.INT0IF = 0;
}
void main(void) {
    INTCON2=0x00;
    RCONbits.IPEN = 1;
    INTCONbits.GIE = 1;
    INTCONbits.INT0IE = 1;
    
    TRISA = 0;        //LED燈
    TRISB = 1;      //將RB0設為輸入，按鈕
    //TRISC SET FROM CCP1
    TRISD = 0;		// portD is 7-segment display
    TRISE = 0;        //mode output(connect other 晶片)
    
	while(1)
	{   
        SYSTEM_Initialize();
        switch(mode){
            case(0):
                LATE = 0x0;
                seg_port=zero;
                if(lastmode != mode){
                    UART_Write_Text("M   M                    CCC h                t\r\nMM MM                   C    h        ii      t\r\nM M M eee rrr rrr y  y  C    hhh  rrr     ss ttt mmmm   aa  ss \r\nM   M e e r   r   y  y  C    h  h r   ii  s   t  m m m a a  s\r\nM   M ee  r   r    yyy   CCC h  h r   ii ss   tt m m m aaa ss\r\n                     y\r\n                  yyy\r\n");
                }
                lastmode = 0;
                
                LATA = 0xFF;
                __delay_ms(3000);
                break;
            case(1):
                LATE = 0x1;
                seg_port=one;
                if(lastmode != mode){
                    UART_Write_Text(" ****     ****\r\n/**/**   **/**                        **   **\r\n/**//** ** /**  *****  ****** ****** //** **\r\n /** //***  /** **///**//**//*//**//*  //***\r\n/**  //*   /**/******* /** /  /** /    /**\r\n/**   /    /**/**////  /**    /**      **\r\n/**        /**//******/***   /***     **\r\n//         //  ////// ///    ///     //\r\n   ******  **             **           **\r\n  **////**/**            //           /**\r\n **    // /**      ****** **  ****** ****** **********   ******    ******\r\n/**       /****** //**//*/** **//// ///**/ //**//**//** //////**  **////\r\n/**       /**///** /** / /**//*****   /**   /** /** /**  ******* //*****\r\n//**    **/**  /** /**   /** /////**  /**   /** /** /** **////**  /////**\r\n //****** /**  /**/***   /** ******   //**  *** /** /**//******** ******\r\n  //////  //   // ///    // //////     //  ///  //  //  //////// //////\r\n");
                }
                lastmode = 1;
                LATA = 0xFF;
                __delay_ms(2500);
                LATA = 0;
                __delay_ms(2500);
                break;
            case(2):
                LATE = 0x2;
                seg_port=two;
                if(lastmode != mode){
                    UART_Write_Text("  o          o                                                 \r\n <|\\        /|>                                                \r\n / \\o    o// \\                                                \r\n \\o/ v\\  /v \\o/    o__  __o   \\o__ __o   \\o__ __o    o      o  \r\n  |   <\\/>   |    /v      |>   |     |>   |     |>  <|>    <|> \r\n / \\        / \\  />      //   / \\   < >  / \\   < >  < >    < > \r\n \\o/        \\o/  \\o    o/     \\o/        \\o/         \\o    o/  \r\n  |          |    v\\  /v __o   |          |           v\\  /v   \r\n / \\        / \\    <\\/> __/>  / \\        / \\           <\\/>    \r\n                                                        /      \r\n                                                       o       \r\n                                                    __/>       \r\n      o__ __o     o                       o                o                                              \r\n     /v     v\\   <|>                    _<|>_             <|>                                             \r\n    />       <\\  / >                                      < >                                             \r\n  o/             \\o__ __o    \\o__ __o     o        __o__   |      \\o__ __o__ __o      o__ __o/      __o__ \r\n <|               |     v\\    |     |>   <|>      />  \\    o__/_   |     |     |>    /v     |      />  \\  \r\n  \\             / \\     <\\  / \\   < >   / \\      \\o       |      / \\   / \\   / \\   />     / \\     \\o     \r\n    \\         /  \\o/     o/  \\o/         \\o/       v\\      |      \\o/   \\o/   \\o/   \\      \\o/      v\\    \r\n     o       o    |     <|    |           |         <\\     o       |     |     |     o      |        <\\   \r\n     <\\__ __/>   / \\    / \\  / \\         / \\   _\\o__</     <\\__   / \\   / \\   / \\    <\\__  / \\  _\\o__</   \r\n");
                }
                lastmode = 2;
                LATA = 0x55;
                __delay_ms(3000);
                LATA = 0xAA;
                __delay_ms(3000);
                break;
            case(3):
                LATE = 0x3;
                seg_port=three;
                if(lastmode != mode){
                    UART_Write_Text(".88b  d88. d88888b d8888b. d8888b. db    db \r\n88'YbdP`88 88'     88  `8D 88  `8D `8b  d8' \r\n88  88  88 88ooooo 88oobY' 88oobY'  `8bd8'  \r\n88  88  88 88~~~~~ 88`8b   88`8b      88    \r\n88  88  88 88.     88 `88. 88 `88.    88    \r\nYP  YP  YP Y88888P 88   YD 88   YD    YP    \r\n \r\n \r\n .o88b. db   db d8888b. d888888b .d8888. d888888b .88b  d88.  .d8b.  .d8888. \r\nd8P  Y8 88   88 88  `8D   `88'   88'  YP `~~88~~' 88'YbdP`88 d8' `8b 88'  YP \r\n8P      88ooo88 88oobY'    88    `8bo.      88    88  88  88 88ooo88 `8bo.   \r\n8b      88~~~88 88`8b      88      `Y8b.    88    88  88  88 88~~~88   `Y8b. \r\nY8b  d8 88   88 88 `88.   .88.   db   8D    88    88  88  88 88   88 db   8D \r\n `Y88P' YP   YP 88   YD Y888888P `8888Y'    YP    YP  YP  YP YP   YP `8888Y' \r\n");
                }
                lastmode = 3;
                LATA = 0x33;
                __delay_ms(3000);
                LATA = 0xCC;
                __delay_ms(3000);
                break;
            case(4):
                LATE = 0x4;
                seg_port=four;
                if(lastmode != mode){
                    UART_Write_Text(".___  ___.  _______ .______      .______     ____    ____\r\n|   \\/   | |   ____||   _  \\     |   _  \\    \\   \\  /   /\r\n|  \\  /  | |  |__   |  |_)  |    |  |_)  |    \\   \\/   /\r\n|  |\\/|  | |   __|  |      /     |      /      \\_    _/\r\n|  |  |  | |  |____ |  |\\  \\----.|  |\\  \\----.   |  |\r\n|__|  |__| |_______|| _| `._____|| _| `._____|   |__|\r\n                                                          \r\n  ______  __    __  .______       __       _______.___________..___  ___.      ___           _______.\r\n /      ||  |  |  | |   _  \\     |  |     /       |           ||   \\/   |     /   \\         /       |\r\n|  ,----'|  |__|  | |  |_)  |    |  |    |   (----`---|  |----`|  \\  /  |    /  ^  \\       |   (----`\r\n|  |     |   __   | |      /     |  |     \\   \\       |  |     |  |\\/|  |   /  /_\\  \\       \\   \\    \r\n|  `----.|  |  |  | |  |\\  \\----.|  | .----)   |      |  |     |  |  |  |  /  _____  \\  .----)   |   \r\n \\______||__|  |__| | _| `._____||__| |_______/       |__|     |__|  |__| /__/     \\__\\ |_______/    \r\n \r\n");
                }
                lastmode = 4;       
                LATA = 0x03;
                __delay_ms(3000);
                LATA = 0x0C;
                __delay_ms(3000);
                LATA = 0x30;
                __delay_ms(3000);
                LATA = 0xC0;
                __delay_ms(3000);
                break;
            case(5):
                LATE = 0x5;
                seg_port=five;
                if(lastmode != mode){
                    UART_Write_Text("_|      _|           \r\n_|_|  _|_|    _|_|    _|  _|_|  _|  _|_|  _|    _|  \r\n_|  _|  _|  _|_|_|_|  _|_|      _|_|      _|    _|  \r\n_|      _|  _|        _|        _|        _|    _|  \r\n_|      _|    _|_|_|  _|        _|          _|_|_|  \r\n                                                _|  \r\n                                            _|_|    \r\n                                                                                          \r\n  _|_|_|  _|                  _|              _|                                          \r\n_|        _|_|_|    _|  _|_|        _|_|_|  _|_|_|_|  _|_|_|  _|_|      _|_|_|    _|_|_|  \r\n_|        _|    _|  _|_|      _|  _|_|        _|      _|    _|    _|  _|    _|  _|_|      \r\n_|        _|    _|  _|        _|      _|_|    _|      _|    _|    _|  _|    _|      _|_|  \r\n  _|_|_|  _|    _|  _|        _|  _|_|_|        _|_|  _|    _|    _|    _|_|_|  _|_|_|    \r\n");
                }
                lastmode = 5;
                LATA = 0x99;
                __delay_ms(3000);
                LATA = 0x66;
                __delay_ms(3000);
                break;
            case(6):
                LATE = 0x6;
                seg_port=six;
                if(lastmode != mode){
                    UART_Write_Text(" __  __  ____  ____  ____  _  _     ___  _   _  ____  ____  ___  ____  __  __    __    ___ \r\n(  \\/  )( ___)(  _ \\(  _ \\( \\/ )   / __)( )_( )(  _ \\(_  _)/ __)(_  _)(  \\/  )  /__\\  / __)\r\n )    (  )__)  )   / )   / \\  /   ( (__  ) _ (  )   / _)(_ \\__ \\  )(   )    (  /(__)\\ \\__ \\\r\n(_/\\/\\_)(____)(_)\\_)(_)\\_) (__)    \\___)(_) (_)(_)\\_)(____)(___/ (__) (_/\\/\\_)(__)(__)(___/\r\n");
                }
                lastmode = 6;
                LATA = 0xC3;
                __delay_ms(3000);
                LATA = 0x3C;
                __delay_ms(3000);
                break;
            case(7):
                LATE = 0x7;
                seg_port=seven;
                if(lastmode != mode){
                    UART_Write_Text("     /\\__\\         /\\  \\         /\\  \\         /\\  \\         |\\__\\    \r\n    /::|  |       /::\\  \\       /::\\  \\       /::\\  \\        |:|  |   \r\n   /:|:|  |      /:/\\:\\  \\     /:/\\:\\  \\     /:/\\:\\  \\       |:|  |   \r\n  /:/|:|__|__   /::\\~\\:\\  \\   /::\\~\\:\\  \\   /::\\~\\:\\  \\      |:|__|__ \r\n /:/ |::::\\__\\ /:/\\:\\ \\:\\__\\ /:/\\:\\ \\:\\__\\ /:/\\:\\ \\:\\__\\     /::::\\__\\\r\n \\/__/~~/:/  / \\:\\~\\:\\ \\/__/ \\/_|::\\/:/  / \\/_|::\\/:/  /    /:/~~/~   \r\n       /:/  /   \\:\\ \\:\\__\\      |:|::/  /     |:|::/  /    /:/  /     \r\n      /:/  /     \\:\\ \\/__/      |:|\\/__/      |:|\\/__/     \\/__/      \r\n     /:/  /       \\:\\__\\        |:|  |        |:|  |                  \r\n     \\/__/         \\/__/         \\|__|         \\|__|                  \r\n      ___           ___           ___                       ___           ___           ___           ___           ___     \r\n     /\\  \\         /\\__\\         /\\  \\          ___        /\\  \\         /\\  \\         /\\__\\         /\\  \\         /\\  \\    \r\n    /::\\  \\       /:/  /        /::\\  \\        /\\  \\      /::\\  \\        \\:\\  \\       /::|  |       /::\\  \\       /::\\  \\   \r\n   /:/\\:\\  \\     /:/__/        /:/\\:\\  \\       \\:\\  \\    /:/\\ \\  \\        \\:\\  \\     /:|:|  |      /:/\\:\\  \\     /:/\\ \\  \\  \r\n  /:/  \\:\\  \\   /::\\  \\ ___   /::\\~\\:\\  \\      /::\\__\\  _\\:\\~\\ \\  \\       /::\\  \\   /:/|:|__|__   /::\\~\\:\\  \\   _\\:\\~\\ \\  \\ \r\n /:/__/ \\:\\__\\ /:/\\:\\  /\\__\\ /:/\\:\\ \\:\\__\\  __/:/\\/__/ /\\ \\:\\ \\ \\__\\     /:/\\:\\__\\ /:/ |::::\\__\\ /:/\\:\\ \\:\\__\\ /\\ \\:\\ \\ \\__\\\r\n \\:\\  \\  \\/__/ \\/__\\:\\/:/  / \\/_|::\\/:/  / /\\/:/  /    \\:\\ \\:\\ \\/__/    /:/  \\/__/ \\/__/~~/:/  / \\/__\\:\\/:/  / \\:\\ \\:\\ \\/__/\r\n  \\:\\  \\            \\::/  /     |:|::/  /  \\::/__/      \\:\\ \\:\\__\\     /:/  /            /:/  /       \\::/  /   \\:\\ \\:\\__\\  \r\n   \\:\\  \\           /:/  /      |:|\\/__/    \\:\\__\\       \\:\\/:/  /     \\/__/            /:/  /        /:/  /     \\:\\/:/  /  \r\n    \\:\\__\\         /:/  /       |:|  |       \\/__/        \\::/  /                      /:/  /        /:/  /       \\::/  /   \r\n     \\/__/         \\/__/         \\|__|                     \\/__/                       \\/__/         \\/__/         \\/__/    \r\n");
                }
                lastmode = 7;
                LATA = 0xFF;
                __delay_ms(6000);
                LATA = 0x00;
                __delay_ms(3000);
                break;
        }
    }
    return;
}

