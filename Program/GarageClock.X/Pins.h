#ifndef PINS_H
#define	PINS_H

#include <xc.h>

#define OutputPinDirection 0
#define InputPinDirection  1

#define LowPinLevel  0
#define HighPinLevel 1

// Выводы индикаторов времени (слева направо)
#define Time1Pin          RB5
#define Time1PinDirection TRISB5
#define Time2Pin          RB2
#define Time2PinDirection TRISB2
#define Time3Pin          RB1
#define Time3PinDirection TRISB1
#define Time4Pin          RC7
#define Time4PinDirection TRISC7

// Выводы сегментов индикаторов времени
#define TimeAPin          RB4
#define TimeAPinDirection TRISB4
#define TimeBPin          RC6
#define TimeBPinDirection TRISC6
#define TimeCPin          RD5
#define TimeCPinDirection TRISD5
#define TimeDPin          RD7
#define TimeDPinDirection TRISD7
#define TimeEPin          RD2
#define TimeEPinDirection TRISD2
#define TimeFPin          RB3
#define TimeFPinDirection TRISB3
#define TimeGPin          RD4
#define TimeGPinDirection TRISD4
#define TimeHPin          RD6
#define TimeHPinDirection TRISD6

// Знак минуса для индикатора температуры
#define TemperatureSignPin          RA0
#define TemperatureSignPinDirection TRISA0

// Выводы индикаторов температуры (слева направо)
#define Temperature1Pin          RE0
#define Temperature1PinDirection TRISE0
#define Temperature2Pin          RA5
#define Temperature2PinDirection TRISA5
#define Temperature3Pin          RD0
#define Temperature3PinDirection TRISD0

// Выводы сегментов индикаторов температуры
#define TemperatureAPin          RE1
#define TemperatureAPinDirection TRISE1
#define TemperatureBPin          RA3
#define TemperatureBPinDirection TRISA3
#define TemperatureCPin          RC1
#define TemperatureCPinDirection TRISC1
#define TemperatureDPin          RA2
#define TemperatureDPinDirection TRISA2
#define TemperatureEPin          RA1
#define TemperatureEPinDirection TRISA1
#define TemperatureFPin          RE2
#define TemperatureFPinDirection TRISE2
#define TemperatureGPin          RC2
#define TemperatureGPinDirection TRISC2
#define TemperatureHPin          RC0
#define TemperatureHPinDirection TRISC0

// Выводы кнопок
#define ButtonHoursPin            RC5
#define ButtonHoursPinDirection   TRISC5
#define ButtonMinutesPin          RD3
#define ButtonMinutesPinDirection TRISD3

// Значение вывода кнопки при нажатом состоянии
#define ButtonPressed 0

// Вывод шины 1-Wire
#define OneWirePin          RB7
#define OneWirePinDirection TRISB7

// Выводы шины I2C
#define I2CSCLDirection TRISC3
#define I2CSDADirection TRISC4

#endif /* PINS_H */
