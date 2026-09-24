#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "Motor.h"

#include <Wire.h>
#include "pin_config.h"


#define STEP_INTERVAL           1500
#define STEPS_PER_REVOLUTION    5000

//High is clockwise, according to old code
#define MOTORSTATE_TO_PINOUT(X) (X == MOTORSTATE_DEPLOYED ? HIGH : LOW)

//todo should i really dedicate a struct to this
static struct {
    uint32_t last_swap;
    uint16_t working_steps;
} Motor_Ctx;

int MotorCtx_Init() {
    pinMode(PIN_MOTOR_DIRECTION,    OUTPUT);
    pinMode(PIN_MOTOR_STEP,         OUTPUT);
    pinMode(PIN_MOTOR_MS1,          OUTPUT);
    pinMode(PIN_MOTOR_MS2,          OUTPUT);
    pinMode(PIN_MOTOR_MS3,          OUTPUT);

    digitalWrite(PIN_MOTOR_DIRECTION, MOTORSTATE_TO_PINOUT(MOTORSTATE_RETRACT));
    digitalWrite(PIN_MOTOR_STEP, LOW);

    digitalWrite(PIN_MOTOR_MS1, LOW); //Todo why low?
    digitalWrite(PIN_MOTOR_MS2, LOW); //Todo why low?
    digitalWrite(PIN_MOTOR_MS3, LOW); //Todo why low?
    

    Motor_Ctx.working_steps     = 0;
    Motor_Ctx.last_swap         = -1;
}



int MotorCtx_Poll(uint32_t time) {
    if (Motor_Ctx.working_steps == 0) return 0;
    if (time - Motor_Ctx.last_swap >= STEP_INTERVAL) {
        //todo decrement in here is not really readable.
        digitalWrite(PIN_MOTOR_STEP, (Motor_Ctx.working_steps-- % 2 == 0) ? HIGH : LOW);
        Motor_Ctx.last_swap = time;
    }
    return Motor_Ctx.working_steps;
}
int MotorCtx_SetState(MOTORSTATE state) {
    digitalWrite(PIN_MOTOR_DIRECTION, MOTORSTATE_TO_PINOUT(state));
    Motor_Ctx.working_steps     = (STEPS_PER_REVOLUTION * 2);
    Motor_Ctx.last_swap         = -1;
}


