/** SevenSegmentDisplayDS18B20.h
 * v.1.2
 */

#ifndef SEVENSEGMENTDISPLAYDS18B20_H
#define	SEVENSEGMENTDISPLAYDS18B20_H

/** Выводит значение температуры с датчика DS18B20 на три семисегментных индикатора.
 * @param indicatorValues Массив, в который будет выведено значение температуры. Массив должен иметь длину равную трем.
 */
void FillIndicators3WithDS18B20Temperature(unsigned char* indicatorValues);

/** Выводит значение температуры с датчика DS18B20 на индикатор символа "минус" и три семисегментных индикатора.
 * @param indicatorValues Массив, в который будет выведено значение температуры. Массив должен иметь длину равную трем.
 * @param indicatorSign Указатель на переменную, в которую будет записано состояние индикатора символа "минус" (включен или выключен).
 */
void FillIndicators3AndSignWithDS18B20Temperature(unsigned char* indicatorValues, unsigned char* indicatorSign);

#endif	/* SEVENSEGMENTDISPLAYDS18B20_H */
