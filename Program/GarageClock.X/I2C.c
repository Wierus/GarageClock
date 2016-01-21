#include "I2C.h"

void I2CInit() {
    I2CSCLDirection = InputPinDirection;
    I2CSDADirection = InputPinDirection;
    SSPSTAT |= 0x80;
    SSPCON = 0x28;
    SSPADD = 0x28;
}

void I2CStart() {
    SEN = 1;
    while (SEN);
}

void I2CStop() {
    PEN = 1;
    while (PEN);
}

void I2CRestart() {
    RSEN = 1;
    while (RSEN);
}

void I2CAck() {
    ACKDT = 0;
    ACKEN = 1;
    while (ACKEN);
}

void I2CNak() {
    ACKDT = 1;
    ACKEN = 1;
    while (ACKEN);
}

void I2CWait() {
    while ((SSPCON2 & 0x1F) || (SSPSTAT & 0x04));
}

void I2CWrite(unsigned char value) {
    SSPBUF = value;
    while (BF);
    I2CWait();
}

unsigned char I2CRead() {
    RCEN = 1;
    while (!BF);
    unsigned char value = SSPBUF;
    I2CWait();
    return value;
}
