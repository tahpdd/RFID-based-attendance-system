#ifndef _SERVO_H_
#define _SERVO_H_

#include "main.h"

#define CENTER_DUTY_CYCLE			0.015 //microsecond
#define MAX_DURATION				2 	  //millisecond
#define CALC_LOAD_VAL(HTIM, DUTY_CYCLE) (uint16_t)((DUTY_CYCLE / 100) * HTIM->Instance->ARR)

typedef struct {
	TIM_HandleTypeDef *htim;
	uint32_t channel;
	float max_angle, min_duty_cycle, max_duty_cycle;
} ServoHandlerTypeDef;

void servoInit(ServoHandlerTypeDef*, TIM_HandleTypeDef*, uint32_t, float, float, float);
HAL_StatusTypeDef servoStart(ServoHandlerTypeDef*);
void setServoAngle(ServoHandlerTypeDef*, float);

#endif
