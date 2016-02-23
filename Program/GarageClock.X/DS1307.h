/** DS1307.h
 * v.1.1
 */

#ifndef DS1307_H
#define	DS1307_H

#include "I2C.h"
#include "Math.h"

/** Адреса регистров.
 */
typedef enum DS1307RegisterAdresses {

    SecondsAddress = 0x00,
    MinutesAddress = 0x01,
    HoursAddress   = 0x02,
    DayAddress     = 0x03,
    DateAddress    = 0x04,
    MonthAddress   = 0x05,
    YearAddress    = 0x06,
    ControlAddress = 0x07,

} DS1307RegisterAdresses;

/** Маска бита остановки часов (бит равен "1" - часы остановлены, бит равен "0" - часы запущены).
 * Данный бит находится в регистре секунд.
 */
#define DS1307ClockHaltMask 0b10000000

#define DS1307WriteAddress 0xD0

#define DS1307ReadAddress  0xD1

void DS1307StartClock();

unsigned char DS1307Read(unsigned short address);

void DS1307Write(unsigned short address, unsigned char value);

unsigned char GetIncrementedBCDHours(unsigned char bcdHours);

unsigned char GetIncrementedBCDMinutes(unsigned char bcdMinutes);

#endif /* DS1307_H */
