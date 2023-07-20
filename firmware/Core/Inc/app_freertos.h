/*
 * app_freertos.h
 *
 *  Created on: Jul 5, 2023
 *      Author: piotr
 */

#ifndef INC_APP_FREERTOS_H_
#define INC_APP_FREERTOS_H_

#ifdef __cplusplus
extern "C" {
#endif

void MX_FREERTOS_Init(void);

void vPlausibilityManagerTask(void *argument);
extern void vLTCManagerTask(void *argument);
extern void vExternalMeasurmentsManagerTask(void *argument);
extern void vLoggerManagerTask(void *argument);
extern void vUSBCommandManagerTask(void *argument);
extern void vCarCANManagerTask(void *argument);
extern void vChargerCANManagerTask(void *argument);
extern void vSOCManagerTask(void *argument);

void SystemClock_Config(void);

#ifdef __cplusplus
}
#endif

#endif /* INC_APP_FREERTOS_H_ */
