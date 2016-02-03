#include "Config.h"
#include "Delay.h"
#include "TaskManager.h"
#include "SevenSegmentDisplay.h"
#include "SevenSegmentDisplayDS18B20.h"
#include "Math.h"
#include "DS1307.h"
#include "DS18B20.h"

/** Время свечения одного индикатора времени (мкс).
 */
#define IndicatorTimeLightingTime        250

/** Время свечения одного индикатора температуры (мкс).
 */
#define IndicatorTemperatureLightingTime 750

#define IndicatorTimeCA

#define IndicatorTemperatureCC

#ifdef IndicatorTimeCA

    /** Значение вывода индикатора времени для его включения.
     */
    #define IndicatorTimeOn  IndicatorCAOn

    /** Значение вывода индикатора времени для его выключения.
     */
    #define IndicatorTimeOff IndicatorCAOff

    /** Значение вывода сегмента индикатора времени для его включения.
     */
    #define SegmentTimeOn    SegmentCAOn

    /** Значение вывода сегмента индикатора времени для его выключения.
     */
    #define SegmentTimeOff   SegmentCAOff

#else

    /** Значение вывода индикатора времени для его включения.
     */
    #define IndicatorTimeOn  IndicatorCCOn

    /** Значение вывода индикатора времени для его выключения.
     */
    #define IndicatorTimeOff IndicatorCCOff

    /** Значение вывода сегмента индикатора времени для его включения.
     */
    #define SegmentTimeOn    SegmentCCOn

    /** Значение вывода сегмента индикатора времени для его выключения.
     */
    #define SegmentTimeOff   SegmentCCOff

#endif

#ifdef IndicatorTemperatureCA

    /** Значение вывода индикатора температуры для его включения.
     */
    #define IndicatorTemperatureOn  IndicatorCAOn

    /** Значение вывода индикатора температуры для его выключения.
     */
    #define IndicatorTemperatureOff IndicatorCAOff

    /** Значение вывода сегмента индикатора температуры для его включения.
     */
    #define SegmentTemperatureOn    SegmentCAOn

    /** Значение вывода сегмента индикатора температуры для его выключения.
     */
    #define SegmentTemperatureOff   SegmentCAOff

#else

    /** Значение вывода индикатора температуры для его включения.
     */
    #define IndicatorTemperatureOn  IndicatorCCOn

    /** Значение вывода индикатора температуры для его выключения.
     */
    #define IndicatorTemperatureOff IndicatorCCOff

    /** Значение вывода сегмента индикатора температуры для его включения.
     */
    #define SegmentTemperatureOn    SegmentCCOn

    /** Значение вывода сегмента индикатора температуры для его выключения.
     */
    #define SegmentTemperatureOff   SegmentCCOff

#endif

/** Количество индикаторов времени.
 */
#define IndicatorsTimeCount 4

/** Количество индикаторов температуры.
 */
#define IndicatorsTemperatureCount 3

/** Символы на индикаторах времени (слева направо).
 */
unsigned char indicatorTimeValues[IndicatorsTimeCount];

/** Символы на индикаторах температуры (слева направо).
 */
unsigned char indicatorTemperatureValues[IndicatorsTemperatureCount];

/** Количество миллисекунд в секунде.
 */
#define MaxMSeconds 1000

/** Количество микросекунд в миллисекунде.
 */
#define MaxUSeconds 1000

/** Количество наносекунд в микросекунде.
 */
#define MaxNSeconds 1000

/** Значение часов в BCD-формате, полученное с DS1307.
 */
unsigned char timeBCDHours = 0;

/** Значение минут в BCD-формате, полученное с DS1307.
 */
unsigned char timeBCDMinutes = 0;

/** Текущее значение миллисекунд на контроллере.
 */
unsigned short timeMSeconds = 0;

/** Текущее значение микросекунд на контроллере.
 */
unsigned short timeUSeconds = 0;

/** Текущее значение наносекунд на контроллере.
 */
unsigned short timeNSeconds = 0;

/** Устанавливаемая разрешающая способность датчика DS18B20.
 */
#define DS18B20Resolution DS18B20Resolution12Bit

/** Необходимое время удержания кнопки до совершения действия (в единицах T_INT, параметр - в секундах).
 */
#define ButtonPressedTime GetTaskManagerTimerTime(0.5)

/** Текущее время удержания кнопки "Часы" (в единицах T_INT).
 */
unsigned char buttonHoursPressedTimer = 0;

/** Текущее время удержания кнопки "Минуты" (в единицах T_INT).
 */
unsigned char buttonMinutesPressedTimer = 0;

/** Текущее время удержания виртуальной кнопки "Коррекция" (в единицах T_INT).
 */
unsigned char buttonCorrectionPressedTimer = 0;

/** Флаг, показывающий, что кнопка "Часы" нажата.
 */
bit isButtonHoursPressed = 0;

/** Флаг, показывающий, что кнопка "Минуты" нажата.
 */
bit isButtonMinutesPressed = 0;

/** Флаг, показывающий, что виртуальная кнопка "Коррекция" нажата (одновременное нажатие кнопок "Часы" и "Минуты").
 */
bit isButtonCorrectionPressed = 0;

/** Задержка до выполнения задачи DrawIndicatorsTask (в единицах T_INT, параметр - в секундах).
 */
#define DrawIndicatorsTaskDelay            GetTaskManagerTimerTime( 0.0)

/** Задержка до выполнения задачи FillIndicatorsTimeTask (в единицах T_INT, параметр - в секундах).
 */
#define FillIndicatorsTimeTaskDelay        GetTaskManagerTimerTime( 0.0)

/** Задержка до выполнения задачи FillIndicatorsTemperatureTask (в единицах T_INT, параметр - в секундах).
 */
#define FillIndicatorsTemperatureTaskDelay GetTaskManagerTimerTime( 0.0)

/** Задержка до выполнения задачи RefreshTimeTask (в единицах T_INT, параметр - в секундах).
 */
#define RefreshTimeTaskDelay               GetTaskManagerTimerTime( 1.0)

/** Задержка до выполнения задачи RefreshDS18B20Task (в единицах T_INT, параметр - в секундах).
 */
#define RefreshDS18B20TaskDelay            GetTaskManagerTimerTime(10.0)

/** Задержка до выполнения задачи ConvertTemperatureTask (в единицах T_INT, параметр - в секундах).
 */
#define ConvertTemperatureTaskDelay        GetTaskManagerTimerTime( 0.0)

/** Задержка до выполнения задачи GetTemperatureTask (в единицах T_INT, параметр - в секундах).
 */
#define GetTemperatureTaskDelay            GetTaskManagerTimerTime( 1.0)

/** Задержка до выполнения задачи ScanButtonsTask (в единицах T_INT, параметр - в секундах).
 */
#define ScanButtonsTaskDelay               GetTaskManagerTimerTime( 0.0)
        
void IncrementTimeInInterrupt();

void ProcessButtonsInInterrupt();

void NormalizeTime();

/** Обработчик прерывания. Вызывается по переполненеию TMR0 каждые T_INT секунд.
 */
void interrupt Interrupt() {
    if (TMR0IE && TMR0IF) {
        TMR0IF = 0;
        TimerService();
        IncrementTimeInInterrupt();
        ProcessButtonsInInterrupt();
    }
}

// +T_INT
void IncrementTimeInInterrupt() {
    timeMSeconds +=  13;
    timeUSeconds += 107;
    timeNSeconds += 200;
    NormalizeTime();
}

void ProcessButtonsInInterrupt() {
    if ((ButtonHoursPin == ButtonPressed) && (ButtonMinutesPin == ButtonPressed)) {
        buttonCorrectionPressedTimer++;
        if (buttonCorrectionPressedTimer >= ButtonPressedTime) {
            buttonCorrectionPressedTimer -= ButtonPressedTime;
            isButtonCorrectionPressed = 1;
        }
        return;
    }
    else {
        isButtonCorrectionPressed = 0;
        buttonCorrectionPressedTimer = 0;
    }
    if (ButtonHoursPin == ButtonPressed) {
        buttonHoursPressedTimer++;
        if (buttonHoursPressedTimer >= ButtonPressedTime) {
            buttonHoursPressedTimer -= ButtonPressedTime;
            isButtonHoursPressed = 1;
        }
    }
    else {
        isButtonHoursPressed = 0;
        buttonHoursPressedTimer = 0;
    }
    if (ButtonMinutesPin == ButtonPressed) {
        buttonMinutesPressedTimer++;
        if (buttonMinutesPressedTimer >= ButtonPressedTime) {
            buttonMinutesPressedTimer -= ButtonPressedTime;
            isButtonMinutesPressed = 1;
        }
    }
    else {
        isButtonMinutesPressed = 0;
        buttonMinutesPressedTimer = 0;
    }
}

void NormalizeTime() {
    if (timeNSeconds >= MaxNSeconds) {
        timeNSeconds -= MaxNSeconds;
        timeUSeconds++;
    }
    if (timeUSeconds >= MaxUSeconds) {
        timeUSeconds -= MaxUSeconds;
        timeMSeconds++;
    }
    if (timeMSeconds >= MaxMSeconds) {
        timeMSeconds -= MaxMSeconds;
    }
}

void SetIndicatorTimeSegments(unsigned char value) {
    TimeAPin = (value & SegmentA) ? SegmentTimeOn : SegmentTimeOff;
    TimeBPin = (value & SegmentB) ? SegmentTimeOn : SegmentTimeOff;
    TimeCPin = (value & SegmentC) ? SegmentTimeOn : SegmentTimeOff;
    TimeDPin = (value & SegmentD) ? SegmentTimeOn : SegmentTimeOff;
    TimeEPin = (value & SegmentE) ? SegmentTimeOn : SegmentTimeOff;
    TimeFPin = (value & SegmentF) ? SegmentTimeOn : SegmentTimeOff;
    TimeGPin = (value & SegmentG) ? SegmentTimeOn : SegmentTimeOff;
    TimeHPin = (value & SegmentH) ? SegmentTimeOn : SegmentTimeOff;
}

void SetIndicatorTemperatureSegments(unsigned char value) {
    TemperatureAPin = (value & SegmentA) ? SegmentTemperatureOn : SegmentTemperatureOff;
    TemperatureBPin = (value & SegmentB) ? SegmentTemperatureOn : SegmentTemperatureOff;
    TemperatureCPin = (value & SegmentC) ? SegmentTemperatureOn : SegmentTemperatureOff;
    TemperatureDPin = (value & SegmentD) ? SegmentTemperatureOn : SegmentTemperatureOff;
    TemperatureEPin = (value & SegmentE) ? SegmentTemperatureOn : SegmentTemperatureOff;
    TemperatureFPin = (value & SegmentF) ? SegmentTemperatureOn : SegmentTemperatureOff;
    TemperatureGPin = (value & SegmentG) ? SegmentTemperatureOn : SegmentTemperatureOff;
    TemperatureHPin = (value & SegmentH) ? SegmentTemperatureOn : SegmentTemperatureOff;
}

// Объявление задач и действий для них

void DrawIndicatorsTask();
void DrawIndicatorsAction();

void FillIndicatorsTimeTask();
void FillIndicatorsTimeAction();

void FillIndicatorsTemperatureTask();
void FillIndicatorsTemperatureAction();

void RefreshTimeTask();
void RefreshTimeAction();

void RefreshDS18B20Task();
void RefreshDS18B20Action();

void ConvertTemperatureTask();
void ConvertTemperatureAction();

void GetTemperatureTask();
void GetTemperatureAction();

void ScanButtonsTask();
void ScanButtonsAction();

// Определение задач

void DrawIndicatorsTask() {
    DrawIndicatorsAction();
    AddTask(DrawIndicatorsTask, DrawIndicatorsTaskDelay);
}

void FillIndicatorsTimeTask() {
    FillIndicatorsTimeAction();
    AddTask(FillIndicatorsTimeTask, FillIndicatorsTimeTaskDelay);
}

void FillIndicatorsTemperatureTask() {
    FillIndicatorsTemperatureAction();
    AddTask(FillIndicatorsTemperatureTask, FillIndicatorsTemperatureTaskDelay);
}

void RefreshTimeTask() {
    RefreshTimeAction();
    AddTask(RefreshTimeTask, RefreshTimeTaskDelay);
}

void RefreshDS18B20Task() {
    RefreshDS18B20Action();
    AddTask(RefreshDS18B20Task, RefreshDS18B20TaskDelay);
    AddTask(ConvertTemperatureTask, ConvertTemperatureTaskDelay);
}

void ConvertTemperatureTask() {
    ConvertTemperatureAction();
    AddTask(GetTemperatureTask, GetTemperatureTaskDelay);
}

void GetTemperatureTask() {
    GetTemperatureAction();
}

void ScanButtonsTask() {
    ScanButtonsAction();
    AddTask(ScanButtonsTask, ScanButtonsTaskDelay);
}

// Определение действий для задач

void DrawIndicatorsAction() {
    SetIndicatorTimeSegments(indicatorTimeValues[0]);
    Time1Pin = IndicatorTimeOn;
    __delay_us(IndicatorTimeLightingTime);
    Time1Pin = IndicatorTimeOff;
    SetIndicatorTimeSegments(indicatorTimeValues[1]);
    Time2Pin = IndicatorTimeOn;
    __delay_us(IndicatorTimeLightingTime);
    Time2Pin = IndicatorTimeOff;
    SetIndicatorTimeSegments(indicatorTimeValues[2]);
    Time3Pin = IndicatorTimeOn;
    __delay_us(IndicatorTimeLightingTime);
    Time3Pin = IndicatorTimeOff;
    SetIndicatorTimeSegments(indicatorTimeValues[3]);
    Time4Pin = IndicatorTimeOn;
    __delay_us(IndicatorTimeLightingTime);
    Time4Pin = IndicatorTimeOff;
    SetIndicatorTemperatureSegments(indicatorTemperatureValues[0]);
    Temperature1Pin = IndicatorTemperatureOn;
    __delay_us(IndicatorTemperatureLightingTime);
    Temperature1Pin = IndicatorTemperatureOff;
    SetIndicatorTemperatureSegments(indicatorTemperatureValues[1]);
    Temperature2Pin = IndicatorTemperatureOn;
    __delay_us(IndicatorTemperatureLightingTime);
    Temperature2Pin = IndicatorTemperatureOff;
    SetIndicatorTemperatureSegments(indicatorTemperatureValues[2]);
    Temperature3Pin = IndicatorTemperatureOn;
    __delay_us(IndicatorTemperatureLightingTime);
    Temperature3Pin = IndicatorTemperatureOff;
}

void FillIndicatorsTimeAction() {
    indicatorTimeValues[0] = GetD1OfBCD(timeBCDHours) ? GetIndicatorDigit(GetD1OfBCD(timeBCDHours)) : SymbolNull;
    indicatorTimeValues[1] = GetIndicatorDigit(GetD0OfBCD(timeBCDHours));
    if (timeMSeconds >= 500) {
        indicatorTimeValues[1] |= SymbolDot;
    }
    indicatorTimeValues[2] = GetIndicatorDigit(GetD1OfBCD(timeBCDMinutes));
    indicatorTimeValues[3] = GetIndicatorDigit(GetD0OfBCD(timeBCDMinutes));
}

void FillIndicatorsTemperatureAction() {
    unsigned char indicatorSign;
    FillIndicators3AndSignWithDS18B20Temperature(indicatorTemperatureValues, &indicatorSign);
    TemperatureSignPin = indicatorSign;
}

void RefreshTimeAction() {
    timeBCDMinutes = DS1307Read(MinutesAddress);
    timeBCDHours = DS1307Read(HoursAddress);
}

void RefreshDS18B20Action() {
}

void ConvertTemperatureAction() {
    DS18B20ConvertTemperature();
}

void GetTemperatureAction() {
    DS18B20GetTemperature();
}

void ScanButtonsAction() {
    if (isButtonHoursPressed) {
        isButtonHoursPressed = 0;
        timeBCDHours = GetIncrementedBCDHours(timeBCDHours);
        DS1307Write(HoursAddress, timeBCDHours);
    }
    if (isButtonMinutesPressed) {
        isButtonMinutesPressed = 0;
        timeBCDMinutes = GetIncrementedBCDMinutes(timeBCDMinutes);
        DS1307Write(MinutesAddress, timeBCDMinutes);
    }
    if (isButtonCorrectionPressed) {
        isButtonCorrectionPressed = 0;
        if (GetD1OfBCD(timeBCDMinutes) >= 3) {
            timeBCDHours = GetIncrementedBCDHours(timeBCDHours);
            DS1307Write(HoursAddress, timeBCDHours);
        }
        timeBCDMinutes = 0;
        DS1307Write(MinutesAddress, timeBCDMinutes);
        DS1307Write(SecondsAddress, 0);
        timeMSeconds = 0;
        timeUSeconds = 0;
        timeNSeconds = 0;
    }
}

void InitOptionReg();

void InitIntConReg();

void InitADCon0Reg();

void InitADCon1Reg();

void InitRegisters() {
    InitOptionReg();
    InitIntConReg();
    InitADCon0Reg();
    InitADCon1Reg();
    PSPMODE = 0;
}

void InitOptionReg() {
    /** OPTION_REG: bit 2-0
     * PS<2:0>: Prescaler Rate Select bits
     * BIT VALUE | TMR0 RATE | WDT RATE
     * 000       | 1 :   2   | 1 :   1
     * 001       | 1 :   4   | 1 :   2
     * 010       | 1 :   8   | 1 :   4
     * 011       | 1 :  16   | 1 :   8
     * 100       | 1 :  32   | 1 :  16
     * 101       | 1 :  64   | 1 :  32
     * 110       | 1 : 128   | 1 :  64
     * 111       | 1 : 256   | 1 : 128
     */
    OPTION_REGbits.PS = 0b111;
    /** OPTION_REG: bit 3
     * PSA: Prescaler Assignment bit
     * 1 = Prescaler is assigned to the WDT
     * 0 = Prescaler is assigned to the Timer0 module
     */
    OPTION_REGbits.PSA = 0;
    /** OPTION_REG: bit 4
     * T0SE: TMR0 Source Edge Select bit
     * 1 = Increment on high-to-low transition on RA4/T0CKI pin
     * 0 = Increment on low-to-high transition on RA4/T0CKI pin
     */
    OPTION_REGbits.T0SE = 0;
    /** OPTION_REG: bit 5
     * T0CS: TMR0 Clock Source Select bit
     * 1 = Transition on RA4/T0CKI pin
     * 0 = Internal instruction cycle clock (CLKOUT)
     */
    OPTION_REGbits.T0CS = 0;
    /** OPTION_REG: bit 6
     * INTEDG: Interrupt Edge Select bit
     * 1 = Interrupt on rising edge of RB0/INT pin
     * 0 = Interrupt on falling edge of RB0/INT pin
     */ 
     OPTION_REGbits.INTEDG = 0;
    /** OPTION_REG: bit 7
     * RBPU (not): PORTB Pull-up Enable bit
     * 1 = PORTB pull-ups are disabled
     * 0 = PORTB pull-ups are enabled by individual port latch values
     */
    OPTION_REGbits.nRBPU = 1;
}

void InitIntConReg() {
    /** INTCON: bit 0
     * RBIF: RB Port Change Interrupt Flag bit
     * 1 = At least one of the RB7:RB4 pins changed state; a mismatch condition will continue to set the bit. Reading PORTB will end the mismatch condition and allow the bit to be cleared (must be cleared in software)
     * 0 = None of the RB7:RB4 pins have changed state
     */
    /** INTCON: bit 1
     * INTF: RB0/INT External Interrupt Flag bit
     * 1 = The RB0/INT external interrupt occurred (must be cleared in software)
     * 0 = The RB0/INT external interrupt did not occur
     */
    /** INTCON: bit 2
     * T0IF: TMR0 Overflow Interrupt Flag bit
     * 1 = TMR0 register has overflowed (must be cleared in software)
     * 0 = TMR0 register did not overflow
     */
    /** INTCON: bit 3
     * RBIE: RB Port Change Interrupt Enable bit
     * 1 = Enables the RB port change interrupt
     * 0 = Disables the RB port change interrupt
     */
    INTCONbits.RBIE = 0;
    /** INTCON: bit 4
     * INTE: RB0/INT External Interrupt Enable bit
     * 1 = Enables the RB0/INT external interrupt
     * 0 = Disables the RB0/INT external interrupt
     */
    INTCONbits.INTE = 0;
    /** INTCON: bit 5
     * T0IE: TMR0 Overflow Interrupt Enable bit
     * 1 = Enables the TMR0 interrupt
     * 0 = Disables the TMR0 interrupt
     */
    INTCONbits.T0IE = 1;
    /** INTCON: bit 6
     * PEIE: Peripheral Interrupt Enable bit
     * 1 = Enables all unmasked peripheral interrupts
     * 0 = Disables all peripheral interrupts
     */
    INTCONbits.PEIE = 0;
    /** INTCON: bit 7
     * GIE: Global Interrupt Enable bit
     * 1 = Enables all unmasked interrupts
     * 0 = Disables all interrupts
     */
    INTCONbits.GIE = 0;
}

void InitADCon0Reg() {
    /** ADCON0: bit 0
     * ADON: A/D On bit
     * 1 = A/D converter module is operating
     * 0 = A/D converter module is shut-off and consumes no operating current
     */
    ADCON0bits.ADON = 0;
    /** ADCON0: bit 1
     * Unimplemented: Read as '0'
     */
    /** ADCON0: bit 2
     * GO/DONE (not): A/D Conversion Status bit
     * If ADON = 1:
     * 1 = A/D conversion in progress (setting this bit starts the A/D conversion)
     * 0 = A/D conversion not in progress (this bit is automatically cleared by hardware when the A/D conversion is complete)
     */
    /** ADCON0: bit 5-3
     * CHS<2:0>: Analog Channel Select bits
     * 000 = channel 0, (RA0/AN0)
     * 001 = channel 1, (RA1/AN1)
     * 010 = channel 2, (RA2/AN2)
     * 011 = channel 3, (RA3/AN3)
     * 100 = channel 4, (RA5/AN4)
     * 101 = channel 5, (RE0/AN5) (These channels are not available on PIC16F873/876 devices)
     * 110 = channel 6, (RE1/AN6) (These channels are not available on PIC16F873/876 devices)
     * 111 = channel 7, (RE2/AN7) (These channels are not available on PIC16F873/876 devices)
     */
    /** ADCON0: bit 7-6
     * ADCS<1:0>: A/D Conversion Clock Select bits
     * 00 = FOSC/2
     * 01 = FOSC/8
     * 10 = FOSC/32
     * 11 = FRC (clock derived from the internal A/D module RC oscillator)
     */
}

void InitADCon1Reg() {
    /** ADCON1: bit 3-0
     * PCFG<3:0>: A/D Port Configuration Control bits
     * PCFG3:PCFG0 | AN7/RE2 | AN6/RE1 | AN5/RE0 | AN4/RA5 | AN3/RA3 | AN2/RA2 | AN1/RA1 | AN0/RA0 | VREF+ | VREF- | CHAN/Refs
     * 0000        | A       | A       | A       | A       | A       | A       | A       | A       | VDD   | VSS   | 8/0
     * 0001        | A       | A       | A       | A       | VREF+   | A       | A       | A       | RA3   | VSS   | 7/1
     * 0010        | D       | D       | D       | A       | A       | A       | A       | A       | VDD   | VSS   | 5/0
     * 0011        | D       | D       | D       | A       | VREF+   | A       | A       | A       | RA3   | VSS   | 4/1
     * 0100        | D       | D       | D       | D       | A       | D       | A       | A       | VDD   | VSS   | 3/0
     * 0101        | D       | D       | D       | D       | VREF+   | D       | A       | A       | RA3   | VSS   | 2/1
     * 011x        | D       | D       | D       | D       | D       | D       | D       | D       | VDD   | VSS   | 0/0
     * 1000        | A       | A       | A       | A       | VREF+   | VREF-   | A       | A       | RA3   | RA2   | 6/2
     * 1001        | D       | D       | A       | A       | A       | A       | A       | A       | VDD   | VSS   | 6/0
     * 1010        | D       | D       | A       | A       | VREF+   | A       | A       | A       | RA3   | VSS   | 5/1
     * 1011        | D       | D       | A       | A       | VREF+   | VREF-   | A       | A       | RA3   | RA2   | 4/2
     * 1100        | D       | D       | D       | A       | VREF+   | VREF-   | A       | A       | RA3   | RA2   | 3/2
     * 1101        | D       | D       | D       | D       | VREF+   | VREF-   | A       | A       | RA3   | RA2   | 2/2
     * 1110        | D       | D       | D       | D       | D       | D       | D       | A       | VDD   | VSS   | 1/0
     * 1111        | D       | D       | D       | D       | VREF+   | VREF-   | D       | A       | RA3   | RA2   | 1/2
     * A = Analog input, D = Digital I/O
     */
    ADCON1bits.PCFG = 0b0111;
    /** ADCON1: bit 6-4
     * Unimplemented: Read as '0'
     */
    /** ADCON1: bit 7
     * ADFM: A/D Result Format Select bit
     * 1 = Right justified. 6 Most Significant bits of ADRESH are read as '0'
     * 0 = Left justified. 6 Least Significant bits of ADRESL are read as '0'
     */
}

void InitPins() {
    Time1Pin = IndicatorTimeOff;
    Time2Pin = IndicatorTimeOff;
    Time3Pin = IndicatorTimeOff;
    Time4Pin = IndicatorTimeOff;
    Time1PinDirection = OutputPinDirection;
    Time2PinDirection = OutputPinDirection;
    Time3PinDirection = OutputPinDirection;
    Time4PinDirection = OutputPinDirection;
    TimeAPinDirection = OutputPinDirection;
    TimeBPinDirection = OutputPinDirection;
    TimeCPinDirection = OutputPinDirection;
    TimeDPinDirection = OutputPinDirection;
    TimeEPinDirection = OutputPinDirection;
    TimeFPinDirection = OutputPinDirection;
    TimeGPinDirection = OutputPinDirection;
    TimeHPinDirection = OutputPinDirection;
    TemperatureSignPin = 0;
    TemperatureSignPinDirection = OutputPinDirection;
    Temperature1Pin = IndicatorTemperatureOff;
    Temperature2Pin = IndicatorTemperatureOff;
    Temperature3Pin = IndicatorTemperatureOff;
    Temperature1PinDirection = OutputPinDirection;
    Temperature2PinDirection = OutputPinDirection;
    Temperature3PinDirection = OutputPinDirection;
    TemperatureAPinDirection = OutputPinDirection;
    TemperatureBPinDirection = OutputPinDirection;
    TemperatureCPinDirection = OutputPinDirection;
    TemperatureDPinDirection = OutputPinDirection;
    TemperatureEPinDirection = OutputPinDirection;
    TemperatureFPinDirection = OutputPinDirection;
    TemperatureGPinDirection = OutputPinDirection;
    TemperatureHPinDirection = OutputPinDirection;
    ButtonHoursPinDirection   = InputPinDirection;
    ButtonMinutesPinDirection = InputPinDirection;
}

void main() {
    TRISA = 0b11111111;
    TRISB = 0b11111111;
    TRISC = 0b11111111;
    TRISD = 0b11111111;
    TRISE = 0b11111111;
    InitRegisters();
    InitPins();
    I2CInit();
    DS1307StartClock();
    DS18B20SetResolution(DS18B20Resolution);
    InitRTOS();
    RunRTOS();
    AddTask(DrawIndicatorsTask, 0);
    AddTask(FillIndicatorsTimeTask, 0);
    AddTask(FillIndicatorsTemperatureTask, 0);
    AddTask(RefreshTimeTask, 0);
    AddTask(RefreshDS18B20Task, 0);
    AddTask(ScanButtonsTask, 0);
    while (1) {
        di();
        TaskManager();
        ei();
    }
}
