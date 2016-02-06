/** DS18B20Tasks.h
 * v.1.0
 */

#ifndef DS18B20TASKS_H
#define	DS18B20TASKS_H

/** Задержка до выполнения задачи DS18B20InitializeSensorTask (в единицах T_INT, параметр - в секундах).
 */
#define DS18B20InitializeSensorTaskDelay         GetTaskManagerTimerTime(0.0)

/** Задержка до повторного выполнения задачи DS18B20InitializeSensorTask (в единицах T_INT, параметр - в секундах).
 */
#define DS18B20RepeatInitializeSensorTaskDelay   GetTaskManagerTimerTime(1.0)

/** Задержка до выполнения задачи DS18B20ConvertTemperatureTask (в единицах T_INT, параметр - в секундах).
 */
#define DS18B20ConvertTemperatureTaskDelay       GetTaskManagerTimerTime(0.0)

/** Задержка до выполнения задачи DS18B20RepeatConvertTemperatureTask (в единицах T_INT, параметр - в секундах).
 * Это значение равно периоду обновления температуры датчика при штатной работе и при отсутствии ошибок на шине.
 */
#define DS18B20RepeatConvertTemperatureTaskDelay GetTaskManagerTimerTime(5.0)

/** Задержка до выполнения задачи DS18B20GetTemperatureTask (в единицах T_INT, параметр - в секундах).
 */
#define DS18B20GetTemperatureTaskDelay           GetTaskManagerTimerTime(1.0)

/** Задержка до повторного выполнения задачи DS18B20GetTemperatureTask (в единицах T_INT, параметр - в секундах).
 */
#define DS18B20RepeatGetTemperatureTaskDelay     GetTaskManagerTimerTime(0.5)

void DS18B20InitializeSensorTask();
void DS18B20InitializeSensorAction();

void DS18B20ConvertTemperatureTask();
void DS18B20ConvertTemperatureAction();

void DS18B20GetTemperatureTask();
void DS18B20GetTemperatureAction();

#endif /* DS18B20TASKS_H */
