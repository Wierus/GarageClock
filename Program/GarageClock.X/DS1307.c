/** DS1307.c
 * v.1.0
 */

#include "DS1307.h"
#include "Math.h"

void DS1307StartClock() {
    unsigned char seconds = DS1307Read(SecondsAddress);
    if (seconds & DS1307ClockHaltMask) {
        seconds &= !DS1307ClockHaltMask;
        DS1307Write(SecondsAddress, seconds);
    }
}

unsigned char DS1307Read(unsigned short address) {
    unsigned short value;
    I2CStart();
    I2CWrite(DS1307WriteAddress);
    I2CWrite(address);
    I2CRestart();
    I2CWrite(DS1307ReadAddress);
    value = I2CRead();
    I2CNak();
    I2CStop();
    return value;
}

void DS1307Write(unsigned short address, unsigned char value) {
    I2CStart();
    I2CWrite(DS1307WriteAddress);
    I2CWrite(address);
    I2CWrite(value);
    I2CStop();
}

unsigned char GetIncrementedBCDHours(unsigned char bcdHours) {
    unsigned char newD0Hours = GetD0OfBCD(bcdHours) + 1;
    unsigned char newD1Hours = GetD1OfBCD(bcdHours);
    if (newD0Hours == 10) {
        newD0Hours = 0;
        newD1Hours++;
    }
    if ((newD1Hours >= 2) && (newD0Hours >= 4)) {
        newD1Hours = 0;
        newD0Hours = 0;
    }
    return (newD1Hours << 4) | newD0Hours;
}

unsigned char GetIncrementedBCDMinutes(unsigned char bcdMinutes) {
    unsigned char newD0Minutes = GetD0OfBCD(bcdMinutes) + 1;
    unsigned char newD1Minutes = GetD1OfBCD(bcdMinutes);
    if (newD0Minutes == 10) {
        newD0Minutes = 0;
        newD1Minutes++;
    }
    if (newD1Minutes >= 6) {
        newD1Minutes = 0;
        newD0Minutes = 0;
    }
    return (newD1Minutes << 4) | newD0Minutes;
}
