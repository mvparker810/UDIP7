
#include <Arduino.h>
#include <FreeRTOS_ARM.h>

void Master_Module  (void*) {
    for (;;) {
        Serial.println("I am the master\n");
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

void Data_Module  (void*) {
    for (;;) {
        Serial.println("I am the data\n");
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

void Disk_Module  (void*) {
    for (;;) {
        Serial.println("I am the disk\n");
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

void Motor_Module  (void*) {
    for (;;) {
        Serial.println("I am the motor\n");
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}