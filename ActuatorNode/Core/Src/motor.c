#include "motor.h"
#include "tim.h"

void motorInit(
	MotorHandlerTypeDef* 	hmotor,
	TIM_HandleTypeDef*		htim,
	uint32_t 				f_channel,
	uint32_t 				b_channel,
	float 					max_duty_cycle,
	MotorDirection 		direction
){
	hmotor->htim 			= 	htim;
	hmotor->f_channel 		= 	f_channel;
	hmotor->b_channel 		= 	b_channel;
	hmotor->direction 		= 	direction;
	hmotor->L_EN.port 		= 	L_EN_GPIO_Port;
	hmotor->L_EN.pin		= 	L_EN_Pin;
	hmotor->R_EN.port 		= 	R_EN_GPIO_Port;
	hmotor->R_EN.pin		= 	R_EN_Pin;
	hmotor->max_duty_cycle 	= 	max_duty_cycle;

}

void setMotorPWM(MotorHandlerTypeDef *hmotor, float duty_cycle){
	if(duty_cycle >= hmotor->max_duty_cycle){
		duty_cycle = hmotor->max_duty_cycle;
	}

	float load_value = CALC_LOAD_VAL(hmotor->htim, duty_cycle);

	switch(hmotor->direction){
		case CLOCKWISE:
			__HAL_TIM_SET_COMPARE(hmotor->htim, hmotor->f_channel, load_value);
			__HAL_TIM_SET_COMPARE(hmotor->htim, hmotor->b_channel, 0);
			break;
		case C_CLOCKWISE:
			__HAL_TIM_SET_COMPARE(hmotor->htim, hmotor->f_channel, 0);
			__HAL_TIM_SET_COMPARE(hmotor->htim, hmotor->b_channel, load_value);
			break;
		default:
			break;
	}
}

void motorStart(MotorHandlerTypeDef *hmotor){
	HAL_TIM_PWM_Start(hmotor->htim, hmotor->b_channel);
	HAL_TIM_PWM_Start(hmotor->htim, hmotor->f_channel);

	HAL_GPIO_WritePin(hmotor->L_EN.port, hmotor->L_EN.pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(hmotor->R_EN.port, hmotor->R_EN.pin, GPIO_PIN_SET);
}

void changeDirection(MotorHandlerTypeDef *hmotor){
	hmotor->direction = (hmotor->direction ? CLOCKWISE : C_CLOCKWISE);
}
