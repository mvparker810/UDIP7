/*
MOTOR MODULE:

One-shot sequence, then the task deletes itself:
  wait for PIN_DEPLOY high -> deploy loop -> notify Data
  wait for PIN_DEPLOY low -> retract loop -> notify Data
*/
#include "pin_config.h"
#include "main.h"

#define MOTOR_DEPLOY_SIG    HIGH
#define MOTOR_RETRACT_SIG   LOW
#define STEPS_PER_REV       5000
#define FREQ_IN_MS          1500

void Motor_Init() {
    //assert STEPS_PER_REV < UINT16_MAX. todo maybe make a linter for this
    pinMode(PIN_MOTOR_DIRECTION,    OUTPUT);
    pinMode(PIN_MOTOR_STEP,         OUTPUT);
    pinMode(PIN_MOTOR_MS1,          OUTPUT);
    pinMode(PIN_MOTOR_MS2,          OUTPUT);
    pinMode(PIN_MOTOR_MS3,          OUTPUT);

    digitalWrite(PIN_MOTOR_DIRECTION, MOTOR_RETRACT_SIG);
    digitalWrite(PIN_MOTOR_STEP, LOW);
    digitalWrite(PIN_MOTOR_MS1, LOW);
    digitalWrite(PIN_MOTOR_MS2, LOW); 
    digitalWrite(PIN_MOTOR_MS3, LOW);
}

static void actuate_motor(uint8_t dir) {
    digitalWrite(PIN_MOTOR_DIRECTION, dir);
    for (uint16_t i = 0; i < STEPS_PER_REV; i++) {
        digitalWrite(PIN_MOTOR_STEP, HIGH);
        vTaskDelay(pdMS_TO_TICKS(FREQ_IN_MS));
        digitalWrite(PIN_MOTOR_STEP, LOW);
        vTaskDelay(pdMS_TO_TICKS(FREQ_IN_MS));
    }
}

void Motor_Module(void*) {
    // TE1 HIGH means deploy
    // TE1 LOW  means retract
    
    while (!status_get().te1) vTaskDelay(pdMS_TO_TICKS(10));
    actuate_motor(MOTOR_DEPLOY_SIG);
    xTaskNotifyGive(ctx.Data); //tell data module we deployed. collcet sensor stuff

    //Boom deployed. wait to retract
    while (status_get().te1) vTaskDelay(pdMS_TO_TICKS(10));
    
    xTaskNotifyGive(ctx.Data); //tell data we are retracting.
    actuate_motor(MOTOR_RETRACT_SIG);

    //the motor has served its purpose. bye bye
    vTaskDelete(NULL);
}
