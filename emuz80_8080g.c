/*
 * Copyright (c) 2023 @Gazelle8087
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
 * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
 /*!
 * PIC18F47Q84/PIC18F47Q83 ROM RAM and UART emulation firmware
 * 
 * Target: EMUZ80 with 8080 on modified MEZZ8080
 * Compiler: MPLAB XC8 v2.36
 *
 * Modified by Gazelle 
 * Version 1.00 2023/12/15
 */
 /*!
 * PIC18F47Q84/PIC18F47Q83 ROM RAM and UART emulation firmware
 * This single source file contains all code
 *
 * Target: EMUZ80 with 8080
 * Compiler: MPLAB XC8 v2.41
 *
 * Modified by Satoshi Okue https://twitter.com/S_Okue
 * Version 0.1 2023/08/26
 */

/*
 *  PIC18F47Q84 ROM RAM and UART emulation firmware
 *  This single source file contains all code
 *
 *  Original source Written by Tetsuya Suzuki
 *  https://github.com/vintagechips/emuz80
 *  Target: EMUZ80 - The computer with only Z80 and PIC18F47Q43
 *  Compiler: MPLAB XC8 v2.36
 *
 *  Modified by  Gazelle https://twitter.com/Gazelle8087
 *  1st release 2022.7.17
 *
 *  Target: PIC18F47Q84
 *  IDE: MPLAB X v6.0
 *  Compiler: XC8 v2.36
 *
 *  References: source code written by yyhayami
 *  for the CLC configuration and memory mapping/access procedure.
 *  https://github.com/yyhayami/emuz80_hayami/tree/main/emuz80_clc.X
*/

// CONFIG1
#pragma config FEXTOSC = OFF	// External Oscillator Selection (Oscillator not enabled)
#pragma config RSTOSC = HFINTOSC_64MHZ// Reset Oscillator Selection (HFINTOSC with HFFRQ = 64 MHz and CDIV = 1:1)

// CONFIG2
#pragma config CLKOUTEN = OFF	// Clock out Enable bit (CLKOUT function is disabled)
#pragma config PR1WAY = ON		// PRLOCKED One-Way Set Enable bit (PRLOCKED bit can be cleared and set only once)
#pragma config CSWEN = ON		// Clock Switch Enable bit (Writing to NOSC and NDIV is allowed)
#pragma config FCMEN = ON		// Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor enabled)
#ifndef _18F47Q43
#pragma config JTAGEN = OFF
#pragma config FCMENP = OFF
#pragma config FCMENS = OFF
#endif

// CONFIG3
#pragma config MCLRE = EXTMCLR	// MCLR Enable bit (If LVP = 0, MCLR pin is MCLR; If LVP = 1, RE3 pin function is MCLR )
#pragma config PWRTS = PWRT_OFF // Power-up timer selection bits (PWRT is disabled)
#pragma config MVECEN = ON		// Multi-vector enable bit (Multi-vector enabled, Vector table used for interrupts)
#pragma config IVT1WAY = ON		// IVTLOCK bit One-way set enable bit (IVTLOCKED bit can be cleared and set only once)
#pragma config LPBOREN = OFF	// Low Power BOR Enable bit (Low-Power BOR disabled)
#pragma config BOREN = SBORDIS	// Brown-out Reset Enable bits (Brown-out Reset enabled , SBOREN bit is ignored)

// CONFIG4
#pragma config BORV = VBOR_1P9	// Brown-out Reset Voltage Selection bits (Brown-out Reset Voltage (VBOR) set to 1.9V)
#pragma config ZCD = OFF		// ZCD Disable bit (ZCD module is disabled. ZCD can be enabled by setting the ZCDSEN bit of ZCDCON)
#pragma config PPS1WAY = OFF	// PPSLOCK bit One-Way Set Enable bit (PPSLOCKED bit can be set and cleared repeatedly (subject to the unlock sequence))
#pragma config STVREN = ON		// Stack Full/Underflow Reset Enable bit (Stack full/underflow will cause Reset)
#pragma config LVP = ON			// Low Voltage Programming Enable bit (Low voltage programming enabled. MCLR/VPP pin function is MCLR. MCLRE configuration bit is ignored)
#pragma config XINST = OFF		// Extended Instruction Set Enable bit (Extended Instruction Set and Indexed Addressing Mode disabled)

// CONFIG5
#pragma config WDTCPS = WDTCPS_31// WDT Period selection bits (Divider ratio 1:65536; software control of WDTPS)
#pragma config WDTE = OFF		// WDT operating mode (WDT Disabled; SWDTEN is ignored)

// CONFIG6
#pragma config WDTCWS = WDTCWS_7// WDT Window Select bits (window always open (100%); software control; keyed access not required)
#pragma config WDTCCS = SC		// WDT input clock selector (Software Control)

// CONFIG7
#pragma config BBSIZE = BBSIZE_512// Boot Block Size selection bits (Boot Block size is 512 words)
#pragma config BBEN = OFF		// Boot Block enable bit (Boot block disabled)
#pragma config SAFEN = OFF		// Storage Area Flash enable bit (SAF disabled)
#ifdef _18F47Q43
#pragma config DEBUG = OFF		// Background Debugger (Background Debugger disabled)
#endif

// CONFIG8
#pragma config WRTB = OFF		// Boot Block Write Protection bit (Boot Block not Write protected)
#pragma config WRTC = OFF		// Configuration Register Write Protection bit (Configuration registers not Write protected)
#pragma config WRTD = OFF		// Data EEPROM Write Protection bit (Data EEPROM not Write protected)
#pragma config WRTSAF = OFF		// SAF Write protection bit (SAF not Write Protected)
#pragma config WRTAPP = OFF		// Application Block write protection bit (Application Block not write protected)

// CONFIG10
#pragma config CP = OFF		 	// PFM and Data EEPROM Code Protection bit (PFM and Data EEPROM code protection disabled)

#ifndef _18F47Q43
// CONFIG9
#pragma config BOOTPINSEL = RC5	// CRC on boot output pin selection (CRC on boot output pin is RC5)
#pragma config BPEN = OFF		// CRC on boot output pin enable bit (CRC on boot output pin disabled)
#pragma config ODCON = OFF		// CRC on boot output pin open drain bit (Pin drives both high-going and low-going signals)

// CONFIG11
#pragma config BOOTSCEN = OFF	// CRC on boot scan enable for boot area (CRC on boot will not include the boot area of program memory in its calculation)
#pragma config BOOTCOE = HALT	// CRC on boot Continue on Error for boot areas bit (CRC on boot will stop device if error is detected in boot areas)
#pragma config APPSCEN = OFF	// CRC on boot application code scan enable (CRC on boot will not include the application area of program memory in its calculation)
#pragma config SAFSCEN = OFF	// CRC on boot SAF area scan enable (CRC on boot will not include the SAF area of program memory in its calculation)
#pragma config DATASCEN = OFF	// CRC on boot Data EEPROM scan enable (CRC on boot will not include data EEPROM in its calculation)
#pragma config CFGSCEN = OFF	// CRC on boot Config fuses scan enable (CRC on boot will not include the configuration fuses in its calculation)
#pragma config COE = HALT		// CRC on boot Continue on Error for non-boot areas bit (CRC on boot will stop device if error is detected in non-boot areas)
#pragma config BOOTPOR = OFF	// Boot on CRC Enable bit (CRC on boot will not run)

// CONFIG12
#pragma config BCRCPOLT = 0xFF	// Boot Sector Polynomial for CRC on boot bits 31-24 (Bits 31:24 of BCRCPOL are 0xFF)

// CONFIG13
#pragma config BCRCPOLU = 0xFF	// Boot Sector Polynomial for CRC on boot bits 23-16 (Bits 23:16 of BCRCPOL are 0xFF)

// CONFIG14
#pragma config BCRCPOLH = 0xFF	// Boot Sector Polynomial for CRC on boot bits 15-8 (Bits 15:8 of BCRCPOL are 0xFF)

// CONFIG15
#pragma config BCRCPOLL = 0xFF	// Boot Sector Polynomial for CRC on boot bits 7-0 (Bits 7:0 of BCRCPOL are 0xFF)

// CONFIG16
#pragma config BCRCSEEDT = 0xFF	// Boot Sector Seed for CRC on boot bits 31-24 (Bits 31:24 of BCRCSEED are 0xFF)

// CONFIG17
#pragma config BCRCSEEDU = 0xFF	// Boot Sector Seed for CRC on boot bits 23-16 (Bits 23:16 of BCRCSEED are 0xFF)

// CONFIG18
#pragma config BCRCSEEDH = 0xFF	// Boot Sector Seed for CRC on boot bits 15-8 (Bits 15:8 of BCRCSEED are 0xFF)

// CONFIG19
#pragma config BCRCSEEDL = 0xFF	// Boot Sector Seed for CRC on boot bits 7-0 (Bits 7:0 of BCRCSEED are 0xFF)

// CONFIG20
#pragma config BCRCEREST = 0xFF	// Boot Sector Expected Result for CRC on boot bits 31-24 (Bits 31:24 of BCRCERES are 0xFF)

// CONFIG21
#pragma config BCRCERESU = 0xFF	// Boot Sector Expected Result for CRC on boot bits 23-16 (Bits 23:16 of BCRCERES are 0xFF)

// CONFIG22
#pragma config BCRCERESH = 0xFF	// Boot Sector Expected Result for CRC on boot bits 15-8 (Bits 15:8 of BCRCERES are 0xFF)

// CONFIG23
#pragma config BCRCERESL = 0xFF	// Boot Sector Expected Result for CRC on boot bits 7-0 (Bits 7:0 of BCRCERES are 0xFF)

// CONFIG24
#pragma config CRCPOLT = 0xFF	// Non-Boot Sector Polynomial for CRC on boot bits 31-24 (Bits 31:24 of CRCPOL are 0xFF)

// CONFIG25
#pragma config CRCPOLU = 0xFF	// Non-Boot Sector Polynomial for CRC on boot bits 23-16 (Bits 23:16 of CRCPOL are 0xFF)

// CONFIG26
#pragma config CRCPOLH = 0xFF	// Non-Boot Sector Polynomial for CRC on boot bits 15-8 (Bits 15:8 of CRCPOL are 0xFF)

// CONFIG27
#pragma config CRCPOLL = 0xFF	// Non-Boot Sector Polynomial for CRC on boot bits 7-0 (Bits 7:0 of CRCPOL are 0xFF)

// CONFIG28
#pragma config CRCSEEDT = 0xFF	// Non-Boot Sector Seed for CRC on boot bits 31-24 (Bits 31:24 of CRCSEED are 0xFF)

// CONFIG29
#pragma config CRCSEEDU = 0xFF	// Non-Boot Sector Seed for CRC on boot bits 23-16 (Bits 23:16 of CRCSEED are 0xFF)

// CONFIG30
#pragma config CRCSEEDH = 0xFF	// Non-Boot Sector Seed for CRC on boot bits 15-8 (Bits 15:8 of CRCSEED are 0xFF)

// CONFIG31
#pragma config CRCSEEDL = 0xFF	// Non-Boot Sector Seed for CRC on boot bits 7-0 (Bits 7:0 of CRCSEED are 0xFF)

// CONFIG32
#pragma config CRCEREST = 0xFF	// Non-Boot Sector Expected Result for CRC on boot bits 31-24 (Bits 31:24 of CRCERES are 0xFF)

// CONFIG33
#pragma config CRCERESU = 0xFF	// Non-Boot Sector Expected Result for CRC on boot bits 23-16 (Bits 23:16 of CRCERES are 0xFF)

// CONFIG34
#pragma config CRCERESH = 0xFF	// Non-Boot Sector Expected Result for CRC on boot bits 15-8 (Bits 15:8 of CRCERES are 0xFF)

// CONFIG35
#pragma config CRCERESL = 0xFF	// Non-Boot Sector Expected Result for CRC on boot bits 7-0 (Bits 7:0 of CRCERES are 0xFF)
#endif
// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#include <stdio.h>

#define PHI1 RE1
#define PHI2 RA5

#define ROM_TOP 0x0000		// ROM top address
#define ROM_SIZE 0x8000		// 32kB

#define RAM_TOP 0x8000		// RAM top address
#ifdef _18F47Q43
#define RAM_SIZE 0x1000		// 4kB
#else
#define RAM_SIZE 0x3000		// 12kB
#endif

#define UART_DREG 0x00		//Data REG
#define UART_CREG 0x01		//Control REG

#define _XTAL_FREQ 64000000UL

//8080 ROM equivalent, see end of this file
extern const unsigned char rom[];

//8080 RAM equivalent
//volatile unsigned char ram[RAM_SIZE];
unsigned char ram[RAM_SIZE] __at(0x600);

unsigned char ctrl_sig __at(0x500);		//locate at access ram

// UART3 Transmit
void putch(char c) {
	while(!U3TXIF); // Wait or Tx interrupt flag set
	U3TXB = c; // Write data
}

/*
// UART3 Recive
char getch(void) {
	while(!U3RXIF); // Wait for Rx interrupt flag set
	return U3RXB; // Read data
}
*/

// Never called, logically
void __interrupt(irq(default),base(8)) Default_ISR(){}

// main routine
void main(void) {

//	unsigned char ctrl_sig;
	int i;

	// System initialize
	OSCFRQ = 0x08;		// 64MHz internal OSC

	// RESET (RE2) output pin
	ANSELE2 = 0;		// Disable analog function
	LATE2 = 1;			// Reset=Low
	TRISE2 = 0;			// Set as output

//	#define NCO_INC 0x8000  // 64/32 2.00MHz
	#define NCO_INC 0x8421	// 64/31 2.06MHz
//	#define NCO_INC 0x8888	// 64/30 2.13MHz
//	#define NCO_INC 0x8d3d	// 64/29 2.20MHz
//	#define NCO_INC 0x9249	// 64/28 2.28MHz
//	#define NCO_INC 0x97b4	// 64/27 2.37MHz
//	#define NCO_INC 0x9d89	// 64/26 2.46MHz
//	#define NCO_INC 0xa3d7	// 64/25 2.56MHz
//	#define NCO_INC 0xaaaa	// 64/24 2.66MH

	// 8080 clock(PHI1:RA4) by NCO1 Pulse frequency mode
	RA4PPS = 0x3f;		// RA4 assign NCO1
	ANSELA4 = 0;		// Disable analog function
	TRISA4 = 0;			// NCO output pin
	NCO1INC = NCO_INC;	//
	NCO1CLK = 0x40;		// pulse width 4clock Clock source Fosc(62.5msec))
	NCO1PFM = 1;		// Pulse frequency mode
	NCO1OUT = 1;		// NCO output enable

	// 8080 clock(PHI2:RE1) by NCO3 Pulse frequency mode
	RE1PPS = 0x41;		// RE1 assign NCO3
	ANSELE1 = 0;		// Disable analog function
	TRISE1 = 0;			// NCO output pin
	NCO3INC = NCO_INC;	//
	NCO3CLK = 0x80;		// pulse width 16clock Clock source Fosc(250nsec))
	NCO3PFM = 1;		// Pulse frequency mode
	NCO3OUT = 1;		// NCO output enable

	NCO1EN = 1;			// NCO1 enable	Start PHI1
	NOP();				// wait 62.5nsec (seemed OK to remove)
	NCO3EN = 1;			// NCO3 enable	Start PHI2 125nsec after PHI1

	// SYNC (RA0) input pin
	ANSELA0 = 0;		// Disable analog function
	WPUA0 = 1;			// Week pull up
	TRISA0 = 1;			// Set as intput

	// /WR (RA1) input pin
	ANSELA1 = 0;		// Disable analog function
	WPUA1 = 1;			// Week pull up
	TRISA1 = 1;			// Set as intput

	// READY (RA2) output pin
	ANSELA2 = 0;		// Disable analog function
	LATA2 = 1;
	TRISA2 = 0;			// Set as output

	// DBIN (RA3) input pin
	ANSELA3 = 0;		// Disable analog function
	WPUA3 = 1;			// Week pull up
	TRISA3 = 1;			// Set as intput

	// Address bus A15-A8 pin
	ANSELD = 0x00;		// Disable analog function
	WPUD = 0xff;		// Week pull up
	TRISD = 0xff;		// Set as input

	// Address bus A7-A0 pin
	ANSELB = 0x00;		// Disable analog function
	WPUB = 0xff;		// Week pull up
	TRISB = 0xff;		// Set as input

	// Data bus D7-D0 pin
	ANSELC = 0x00;		// Disable analog function
	WPUC = 0xff;		// Week pull up
	TRISC = 0xff;		// Set as input(default)

	// INT (RE0) output pin
	ANSELE0 = 0;		// Disable analog function
	LATE0 = 0;
	TRISE0 = 0;			// Set as output

	// UART3 initialize
	U3BRG = 416;		// 9600bps @ 64MHz
	U3RXEN = 1;			// Receiver enable
	U3TXEN = 1;			// Transmitter enable

	// UART3 Receiver
	ANSELA7 = 0;		// Disable analog function
	TRISA7 = 1;			// RX set as input
	U3RXPPS = 0x07;		// RA7->UART3:RX3;

	// UART3 Transmitter
	ANSELA6 = 0;		// Disable analog function
	LATA6 = 1;			// Default level
	TRISA6 = 0;			// TX set as output
	RA6PPS = 0x26;		// RA6->UART3:TX3;

	U3ON = 1;			// Serial port enable

	printf("\r\nMEZ8080 %2.3fMHz\r\n",NCO1INC * 6.1035 / 100000);

	//========== CLC input pin assign ===========
	// 0,1,4,5 = Port A, C
	// 2,3,6,7 = Port B, D
	CLCIN0PPS = 0x00;	// RA0 <- SYNC
	CLCIN1PPS = 0x04;	// RA4 <- PHI1
	CLCIN2PPS = 0x1f;	// RD7 <- A15
	CLCIN3PPS = 0x1e;	// RD6 <- A14
	CLCIN4PPS = 0x17;	// RC7 <- status bit7(MEMR)
	CLCIN5PPS = 0x14;	// RC4 <- status bit4(OUT)
	CLCIN6PPS = 0x1d;	// RD5 <- A13
	CLCIN7PPS = 0x1c;	// RD4 <- A12

	//========== CLC1 RAM address 1 decoder 8000 - 9FFF ==========
	// 8000-9FFF CLC1OUT = 1 (in case of Q84,Q83)
	// 8000-8FFF CLC1OUT = 1 (in case of Q43)

	CLCSELECT = 0;		// CLC1 select

	CLCnSEL0 = 2;		// CLCIN2PPS <- A15
	CLCnSEL1 = 3;		// CLCIN3PPS <- A14
	CLCnSEL2 = 6;		// CLCIN6PPS <- A13
#ifndef _18F47Q43
	CLCnSEL3 = 127;		// NC
#else
	CLCnSEL3 = 7;		// CLCIN7PPS <- A12
#endif
	CLCnGLS0 = 0x02;	// A15 no inv
	CLCnGLS1 = 0x04;	// A14 inv
	CLCnGLS2 = 0x10;	// A13 inv
	CLCnGLS3 = 0x40;	// A12 inv

	CLCnPOL = 0x00;		// Not inverted the CLC1 output
	CLCnCON = 0x82;		// 4 input AND

	//========== CLC2 RAM address 2 decoder A000-AFFF ==========
	// A000-AFFF CLC2OUT = 1

	CLCSELECT = 1;		// CLC2 select

	CLCnSEL0 = 2;		// CLCIN2PPS <- A15
	CLCnSEL1 = 3;		// CLCIN3PPS <- A14
	CLCnSEL2 = 6;		// CLCIN6PPS <- A13
	CLCnSEL3 = 7;		// CLCIN7PPS <- A12

	CLCnGLS0 = 0x02;	// A15 no inv
	CLCnGLS1 = 0x04;	// A14 inv
	CLCnGLS2 = 0x20;	// A13 no inv
	CLCnGLS3 = 0x40;	// A12 inv

	CLCnPOL = 0x00;		// Not inverted the CLC2 output
	CLCnCON = 0x82;		// 4 input AND

	//========== CLC3 RAM address decoder bind ==========
	// CLC1 or CLC2 (in case of Q84,Q83)
	// CLC1 		(in case of Q43)
	CLCSELECT = 2;		// CLC3 select

	CLCnSEL0 = 51;		// CLC1
	CLCnSEL1 = 52;		// CLC2
	CLCnSEL2 = 127;		// NC
	CLCnSEL3 = 127;		// NC

#ifndef _18F47Q43
	CLCnGLS0 = 0x02+0x08;	// (CLC1 no inv) or (CLC2 no inv)
#else
	CLCnGLS0 = 0x02;		// CLC1 no inv
#endif
	CLCnGLS1 = 0x40;		// 1 (0inv)
	CLCnGLS2 = 0x40;		// 1 (0inv)
	CLCnGLS3 = 0x40;		// 1 (0inv)

	CLCnPOL = 0x00;		// Not inverted the CLC3 output
	CLCnCON = 0x82;		// 4 input AND

	//========== CLC5 ROM read decode ==========
	CLCSELECT = 4;		// CLC5 select

	CLCnSEL0 = 0;		// CLCIN0PPS <- RA0 <- SYNC
	CLCnSEL1 = 1;		// CLCIN1PPS <- RD4 <- PHI1
	CLCnSEL2 = 4;		// CLCIN4PPS <- RC7 <- status bit7(MEMR)
	CLCnSEL3 = 2;		// CLCIN5PPS <- RD7 <- A15(=0 when ROM area)

	CLCnGLS0 = 0x01+0x04;	// CLK <- SYNC inv + PHI1 inv
	CLCnGLS1 = 0x10+0x80;	// D <- MEMR inv + A15 not inv
	CLCnGLS2 = 0;			// R NC
	CLCnGLS3 = 0;			// S NC

	CLCnPOL = 0x81;		// Q invert CLK inv D not inv
	CLCnCON = 0x84;		// D-FF, no interrupt

	//========== CLC6 RAM read decode ==========
	CLCSELECT = 5;		// CLC6 select

	CLCnSEL0 = 0;		// CLCIN0PPS <- RA0 <- SYNC
	CLCnSEL1 = 1;		// CLCIN1PPS <- RD4 <- PHI1
	CLCnSEL2 = 4;		// CLCIN4PPS <- RC7 <- status bit7(MEMR)
#ifndef _18F47Q43
	CLCnSEL3 = 53;		// CLC1 (=1 when RAM area)
#else
	CLCnSEL3 = 51;		// CLC1 (=1 when RAM area)
#endif
	CLCnGLS0 = 0x01+0x04;	// CLK <- SYNC inv + PHI1 inv
	CLCnGLS1 = 0x10+0x40;	// D <- MEMR inv + CLC1 inv
	CLCnGLS2 = 0;			// R NC
	CLCnGLS3 = 0;			// S NC

	CLCnPOL = 0x81;		// Q invert CLK inv D not inv
	CLCnCON = 0x84;		// D-FF, no interrupt

	//========== CLC8 ROM read decode 2 ==========
	CLCSELECT = 7;		// CLC8 select

	CLCnSEL0 = 2;		// CLCIN2PPS <- A15
	CLCnSEL1 = 4;		// CLCIN4PPS <- RC7 <- status bit7(MEMR)
	CLCnSEL2 = 127;		// NC
	CLCnSEL3 = 127;		// NC

	CLCnGLS0 = 0x01;	// A15 inverted
	CLCnGLS1 = 0x08;	// MEMR not inverted
	CLCnGLS2 = 0x10;	// 1(0 inverted) for AND gate
	CLCnGLS3 = 0x40;	// 1(0 inverted) for AND gate

	CLCnPOL = 0x00;		// Not inverted the CLC1 output
	CLCnCON = 0x82;		// 4 input AND

	//======================================================

	// Unlock IVT
	IVTLOCK = 0x55;
	IVTLOCK = 0xAA;
	IVTLOCKbits.IVTLOCKED = 0x00;

	// Default IVT base address
	IVTBASE = 0x000008;

	// Lock IVT
	IVTLOCK = 0x55;
	IVTLOCK = 0xAA;
	IVTLOCKbits.IVTLOCKED = 0x01;

    BSR = 0;			// BSR 0 fixed
    TBLPTRU = 1;		// TBLTPU always 1 fixed (8080ROM at 10000h)
    CLCSELECT = 0;		// CLCSELECT usually 0
	GIE = 1;			// Global interrupt enable
	LATE2 = 0;			// Release reset

	// 8080 start

	asm(
	"bra	poll_sync			\n"
	"after_RD:					\n"	// Return point after RD cycle<---------
	"btfsc	PORTA,3,c			\n"	// DBIN = 1?
	"bra	after_RD			\n"	// poll DBIN
	"after_RD2:					\n"
	"setf	TRISC,c				\n"	// set data bus input
	"after_WR:					\n"	// Return point after WR cycle<--------
	"btfsc	PIR9,0,c			\n"	// U3RXIF = 1?
	"bsf	LATE,0,c			\n"	// then INT = 1
	"poll_sync:					\n"
	"btfss	PORTA,0,c			\n"	// SYNC = 1?
	"bra	poll_sync			\n"	// poll SYNC
	"movff	PORTC,_ctrl_sig,c	\n"	// get CPU status
	"bcf	LATA,2,c			\n"	// READY = 0
	);
//-----------------------------------------------------------------------------
	asm(						// ROM read
//	"btfsc	_ctrl_sig,7,c	\n"	// status MEMR = 1?
//	"btfsc	PORTD,7,c		\n"	// A15 = 0?
//	"btfss	CLCDATA,4,b		\n"	// CLC5 = 1?
	"btfss	CLCDATA,7,b		\n"	// CLC8 = 1?
	"bra	rom_rd_exit		\n"	// next
	"movff	PORTB,TBLPTRL	\n"
	"movff	PORTD,TBLPTRH	\n"
	"tblrd  *               \n" // TABLAT = ROM(TBLPTRU,H,L)
	"movff  TABLAT,LATC     \n" // PORTC = TABLAT
	"bsf	LATA,2,c		\n"	// READY = 1
	"clrf	TRISC,c			\n"	// set data bus output
	"bra	after_RD		\n"
	"rom_rd_exit:			\n"
	);
//-----------------------------------------------------------------------------
	asm(						// RAM read
//	"btfsc	_ctrl_sig,7,c	\n"	// status MEMR = 1?
//	"btfss	CLCDATA,2,b		\n"	// CLC3 RAM area = 1?
	"btfss	CLCDATA,5,b		\n"	// CLC6 = 1?
	"bra	ram_rd_exit		\n"	// next
	"movff	PORTB,FSR0L		\n" // FSR0L = lower address
	"movf	PORTD,w			\n" // W = upper address
	"addlw	high _ram		\n" // W =+ RAM locate address
	"movwf	FSR0H,c			\n" // FSR0H = W
	"movff	indf0,LATC		\n" // PORTC = RAM(FSR0H,L)
	"bsf	LATA,2,c		\n"	// READY = 1
	"clrf	TRISC,c			\n"	// set data bus output
	"bra	after_RD		\n"
	"ram_rd_exit:			\n"
	);
//-----------------------------------------------------------------------------
	asm(						// IO write
	"btfss	_ctrl_sig,4,c	\n"	// CPUstatus OUT(bit4) = 1?
	"bra	IO_wr_exit		\n"	// next
	"movf	PORTB,w			\n"	// W = PORTD(lower address)
	"btfss	status,2,c		\n"	// if zero skip next bra
	"bra	IO_wr_exit		\n"	// next
	"movff	PORTC,U3TXB		\n"	// U3TXB = PORTC;
	"bsf	LATA,2,c		\n" // READY = 1
	"bra	after_WR		\n"
	"IO_wr_exit:			\n"
	);
//-----------------------------------------------------------------------------			
	asm(						// RAM write
	"btfss	_ctrl_sig,1,c	\n"	// status _WO(bit1) = 1?
	"btfss	CLCDATA,2,b		\n"	// CLC3 RAM area
	"bra	mem_wr_exit		\n"	// next
	"movff	PORTB,FSR0L		\n" // FSR0L = TBLPTRL(lower address)
	"movf	PORTD,w			\n" // W = PORTD(upper address)
	"addlw	high _ram		\n" // W =+ RAM locate address
	"movwf	FSR0H,c			\n" // FSR0H = W
	"movff	PORTC,indf0		\n" // RAM(FSR0H,L) = PORTC
	"bsf	LATA,2,c		\n" // READY = 1
	"bra	after_WR		\n"
	"mem_wr_exit:			\n"
	);
//-----------------------------------------------------------------------------
	asm(						// IO read
	"btfss	_ctrl_sig,6,c	\n"	// CPUstatus INP(bit6) = 1?
	"bra	IO_rd_exit		\n"	// next

	"decfsz	PORTB,w,c		\n" // dec PORTD => WREG (check PORTD = 1?)
	"bra	chk_port00		\n"	// if z=1 skip this instruction
	"clrf	LATC,c			\n" // LATC = 0
	"btfsc	PIR9,1,c		\n" // U3TXIF = 1?
	"bsf	LATC,0,c		\n" // set status bit0
	"btfsc	PIR9,0,c		\n" // U3RXIF = 1?
	"bsf	LATC,1,c		\n"	// set status bit1
	"bsf	LATA,2,c		\n" // READY = 1
	"clrf	TRISC,c			\n" // Set data bus as output
	"bra	after_RD		\n"

	"chk_port00:			\n"
	"incfsz	WREG,w,c		\n"	// inc WREG
	"bra	IO_rd_exit		\n" // if z=1 skip this instruction
	"movff	U3RXB,LATC		\n"	// LATC = U3RXB
	"bcf	LATE,0,c		\n" // INR = 0
	"bsf	LATA,2,c		\n" // READY = 1
	"clrf	TRISC,c			\n" // Set data bus as output
	"bra	after_RD		\n"
	"IO_rd_exit:			\n"
	);
//-----------------------------------------------------------------------------
/* 	if (ctrl_sig & 0x01) {		// Interrupt Acknowledge
		asm(
		"setf	LATC,c			\n"
		"bsf	LATA,2,c		\n"
		"clrf	TRISC,c			\n"
		"bra	after_RD		\n"
		);
	}*/
//-----------------------------------------------------------------------------
	asm(
	"bsf	LATA,2,c		\n"
	"bra	after_WR		\n"
	);
//-----------------------------------------------------------------------------
}

const unsigned char rom[] __at(0x10000) = {
//#include "MSBAS80NI.TXT"
#include "emu8085mon_RevB03_8k.txt"
};

const unsigned char rom_3200[] __at(0x13200)= {
#include "MSBAS80_3200.txt"	
};

const unsigned char ram_5400[] __at(0x15400) = {
#include "game80_8K_5400.txt"
};

const unsigned char ram_5b00[] __at(0x15b00) = {
#include "EMUZ80_ZTB_5B00.txt"
};
