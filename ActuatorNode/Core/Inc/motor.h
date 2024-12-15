#ifndef _MOTOR_H_
#define _MOTOR_H_

#include "main.h"

#define CALC_LOAD_VAL(HTIM, DUTY_CYCLE) (uint16_t)((DUTY_CYCLE / 100) * HTIM->Instance->ARR)

typedef enum{
	CLOCKWISE,
	C_CLOCKWISE,
}MotorDirection;

typedef struct {
	uint32_t f_channel, b_channel;
	TIM_HandleTypeDef *htim;
	struct {
		GPIO_TypeDef* port;
		uint16_t pin;
	} R_EN, L_EN;
	float max_duty_cycle;
	MotorDirection direction;
}MotorHandlerTypeDef;

void motorInit(MotorHandlerTypeDef*, TIM_HandleTypeDef*, uint32_t, uint32_t, float, MotorDirection);
void setMotorPWM(MotorHandlerTypeDef*, float);
void motorStart(MotorHandlerTypeDef*);
void changeDirection(MotorHandlerTypeDef*);

#endif
