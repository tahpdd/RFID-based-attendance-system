#include "servo.h"
#include "tim.h"

void servoInit(
	ServoHandlerTypeDef *servo,
	TIM_HandleTypeDef *htim,
	uint32_t channel,
	float max_angle,
	float max_duty_cycle,
	float min_duty_cycle
){
	servo->htim 			= htim;
	servo->channel 			= channel;
	servo->max_angle 		= max_angle;
	servo->max_duty_cycle 	= max_duty_cycle;
	servo->min_duty_cycle	= min_duty_cycle;
}

HAL_StatusTypeDef servoStart(ServoHandlerTypeDef *servo)
{
	return HAL_TIM_PWM_Start(servo->htim, servo->channel);
}

float calc_DCPR(ServoHandlerTypeDef* hservo){
	float duration_per_degree = MAX_DURATION / hservo->max_angle;
	float timer_period_ms = getTimerPeriod_ms(hservo->htim);
	return duration_per_degree * (1 / timer_period_ms) * 100;
}

static float angle2DutyCycle(ServoHandlerTypeDef *hservo, float rot_angle)
{
	return CENTER_DUTY_CYCLE + rot_angle / calc_DCPR(hservo);
}

static void setServoPWM(ServoHandlerTypeDef *servo, float duty_cycle)
{
	if(duty_cycle > servo->max_duty_cycle){
		duty_cycle = servo->max_duty_cycle;
	}
	else if (duty_cycle < servo->min_duty_cycle){
		duty_cycle = servo->min_duty_cycle;
	}

	float load_value = CALC_LOAD_VAL(servo->htim, duty_cycle);
	__HAL_TIM_SET_COMPARE(servo->htim, servo->channel, load_value);
}

void setServoAngle(ServoHandlerTypeDef* servo, float angle)
{
	if (angle > servo->max_angle){
		angle = servo->max_angle;
	}
	else if (angle < -servo->max_angle){
		angle = -servo->max_angle;
	}

	setServoPWM(servo, angle2DutyCycle(servo, angle));
}
