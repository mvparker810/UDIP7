/*
MASTER MODULE:

Owns the flight status. Only Master writes it; every other task reads it with status_get().
*/
#include <Arduino.h>
#include <FreeRTOS_ARM.h>
#include "pin_config.h"
#include "main.h"

static FlightStatus status;    //never touch directly outside this file

FlightStatus status_get() {
    taskENTER_CRITICAL();   //copy all fields at once so a reader never sees a half-written update
    FlightStatus copy = status;
    taskEXIT_CRITICAL();
    return copy;
}

void status_set_phase(FlightPhase p) {
    taskENTER_CRITICAL();
    status.phase = p;
    taskEXIT_CRITICAL();
}

void Master_Init() {
    status.phase = PHASE_IDLE;
    status.missionMs = 0;
    status.te1 = false;
    pinMode(PIN_DEPLOY, INPUT);
}

void Master_Module(void*) {
    uint32_t t0 = millis();
    TickType_t last = xTaskGetTickCount();
    for (;;) {
        taskENTER_CRITICAL();
        status.missionMs = millis() - t0;
        status.te1 = digitalRead(PIN_DEPLOY);
        taskEXIT_CRITICAL();

        //todo update status.phase as the flight progresses

        vTaskDelayUntil(&last, pdMS_TO_TICKS(10));
    }
}
