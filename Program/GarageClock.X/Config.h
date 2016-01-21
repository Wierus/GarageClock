#ifndef CONFIG_H
#define	CONFIG_H

#include <xc.h>

/** Device: PIC16F877
 * ("16f877.html" and "30292D.pdf")
 */

/** CONFIG: bit 1-0
 * FOSC<1:0>: Oscillator Selection bits
 * 11 = EXTRC = RC oscillator
 * 10 = HS    = HS oscillator
 * 01 = XT    = XT oscillator
 * 00 = LP    = LP oscillator
 */
#pragma config FOSC = HS

/** CONFIG: bit 2
 * WDTE: Watchdog Timer Enable bit
 * 1 = ON  = WDT enabled
 * 0 = OFF = WDT disabled
 */
#pragma config WDTE = OFF

/** CONFIG: bit 3
 * PWRTE (not): Power-up Timer Enable bit
 * 1 = OFF = PWRT disabled
 * 0 = ON  = PWRT enabled
 */
#pragma config PWRTE = OFF

/** CONFIG: bit 13-12, 5-4
 * CP<1:0>: FLASH Program Memory Code Protection bits
 * 11 = OFF       = Code protection off
 * 10 = UPPER_256 = 1F00h to 1FFFh code protected (PIC16F877, 876)
 * 01 = HALF      = 1000h to 1FFFh code protected (PIC16F877, 876)
 * 00 = ALL       = 0000h to 1FFFh code protected (PIC16F877, 876)
 */
#pragma config CP = OFF

/** CONFIG: bit 6
 * BOREN: Brown-out Reset Enable bit
 * 1 = ON  = BOR enabled
 * 0 = OFF = BOR disabled
 */
#pragma config BOREN = OFF

/** CONFIG: bit 7
 * LVP: Low Voltage In-Circuit Serial Programming Enable bit
 * 1 = ON  = RB3/PGM pin has PGM function, low voltage programming enabled
 * 0 = OFF = RB3 is digital I/O, HV on MCLR must be used for programming
 */
#pragma config LVP = OFF

/** CONFIG: bit 8
 * CPD: Data EE Memory Code Protection
 * 1 = OFF = Code protection off
 * 0 = ON  = Data EEPROM memory code protected
 */
#pragma config CPD = OFF

/** CONFIG: bit 9
 * WRT: FLASH Program Memory Write Enable
 * 1 = ON  = Unprotected program memory may be written to by EECON control
 * 0 = OFF = Unprotected program memory may not be written to by EECON control
 */
#pragma config WRT = OFF

/** CONFIG: bit 10
 * Unimplemented: Read as '1'
 */

/** CONFIG: bit 11
 * DEBUG: In-Circuit Debugger Mode
 * 1 = OFF = In-Circuit Debugger disabled, RB6 and RB7 are general purpose I/O pins
 * 0 = ON  = In-Circuit Debugger enabled, RB6 and RB7 are dedicated to the debugger
 */
#pragma config DEBUG = OFF

#endif /* CONFIG_H */
