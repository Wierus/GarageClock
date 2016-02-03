/** I2C.h
 * v.1.0
 */

#ifndef I2C_H
#define	I2C_H

#include "Pins.h"

#ifndef I2CSCLDirection
    #error "I2CSCLDirection symbol is not defined, you should define it in file Pins.h before using this library"
#endif

#ifndef I2CSDADirection
    #error "I2CSDADirection symbol is not defined, you should define it in file Pins.h before using this library"
#endif

/** Initialize I2C in master mode, sets the required baudrate.
 */
void I2CInit();

/** Send a start condition on I2C Bus.
 */
void I2CStart();

/** Send a stop condition on I2C Bus.
 */
void I2CStop();

/** Sends a repeated start condition on I2C Bus.
 */
void I2CRestart();

/** Generates acknowledge for a transfer.
 */
void I2CAck();

/** Generates Not-acknowledge for a transfer.
 */
void I2CNak();

/** Wait for transfer to finish.
 */
void I2CWait();

/** Send 8-bit data on I2C bus.
 * @param value 8-bit data to be sent on bus, data can be either address/data byte.
 */
void I2CWrite(unsigned char value);

/** Read 8-bit data from I2C bus.
 * @return 8-bit data read from I2C bus.
 */
unsigned char I2CRead();

#endif /* I2C_H */
