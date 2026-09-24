#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include <Wire.h>
#include <SPI.h>
#include <SD.h>

#include "IO_Ctx.h"

/*
DUE Specs:
512KB   Flash Memory
96KB    SRAM
single core / no MT

/"skirt deployments looks at the timer signal"

no deployables based on timer

//THRE SIGS to stepper motor
//open gpio
//due rtos

seven segment display (eight plsu decimal)


*/

//in seconds.todo should probably thow these in ms
#define LANDMARK_TE1 80
#define LANDMARK_TE2 322
#define LANDMARK_POWOFF 332


#define PACKET_LOG_DELAY_MS 10      //how periodically do we measure and write a packet in ms
#define PACKET_FLUSH 25             //how many cycles of logging until we flush to the drive

// PIN CONFIG
#define PIN_SD          -1
#define PIN_ACCEL       -1
#define PIN_GYRO        -1
#define PIN_MAGNET      -1
#define PIN_TEMPERATURE -1 //temperature is a long word
#define PIN_IONS        -1


#define PIN_MOTOR_A     -1
#define PIN_MOTOR_B     -1
#define PIN_MOTOR_C     -1

//timer pin
#define PIN_DEPLOY      -1 //TE1 HIGH > DEPLOY. TE1 LOW > RETRACT

//initialize 7seg above all else

// ====================

//todo need stbimg for cam?



static bool     _LOOP;
static IO_Ctx   _IO; //use as opaque handle
uint32_t        _TINIT, _TFINAL; //start and end mission times
static size_t   _TICK;
//todo are times calcualted ourselves, or are we given signals to indicate the stage
void setup() {
    _LOOP = true;
    Wire.begin();
    Wire.setClock(400000); //400kHz

    Serial.begin(115200); 
    while (!Serial) {

    }   

    analogReadResolution(12); //todo 0-4096
    pinMode(PIN_SD,             INPUT);
    pinMode(PIN_ACCEL,          INPUT);
    pinMode(PIN_GYRO,           INPUT);
    pinMode(PIN_MAGNET,         INPUT);
    pinMode(PIN_TEMPERATURE,    INPUT);
    pinMode(PIN_DEPLOY,         INPUT);
    IO_Ctx_Init(&_IO, PIN_SD); //TODO what will the pin be

    //_FILE = fopen("");

    _TINIT = millis(); _TFINAL = 0;
    _TICK = 0;
}




void loop() {
    if (!_LOOP) return;
    uint32_t NOW = millis();
    uint32_t T_PLUS_MS = NOW - _TINIT;

    static bool _SWEEP = false;
    static uint32_t packet_last_ms = 0;
    static uint32_t packet_tick = 0;

    //If we are due for loging data, do it
    if (NOW - packet_last_ms >= PACKET_LOG_DELAY_MS) {
        packet_tick++; 
        packet_last_ms = NOW;
        bool flush = (packet_tick % PACKET_FLUSH == 0); //Flush every PACKET_FLUSH ticks
         
        // if we should be collecting swee pkts and this
        // is an even tick, grab a sweep pkt
        if (_SWEEP && packet_tick % 2) {
            pckt_sweep PCKT = { .TIME = NOW };
            PCKT.val = analogRead(PIN_IONS); //todo this prob changes
           
            IO_Ctx_WritePacket(&_IO, PACKET_SWEEP, (void*)&PCKT);
            if (flush) IO_Ctx_Flush(&_IO, PACKET_SWEEP);
        } else { //else just grab sensor pkts
            pckt_sense PCKT = { .TIME = NOW };
            PCKT.accel          = analogRead(PIN_ACCEL);
            PCKT.gyro           = analogRead(PIN_GYRO);
            PCKT.magnet         = analogRead(PIN_MAGNET);
            PCKT.temperature    = analogRead(PIN_TEMPERATURE);

            IO_Ctx_WritePacket(&_IO, PACKET_SENSE, (void*)&PCKT);
            if (flush) IO_Ctx_Flush(&_IO, PACKET_SENSE);
        }
    }

   
    if (T_PLUS_MS > LANDMARK_TE1) {
        //todo do probe deployment
        //todo would i have to do motor stuff asyncronously

        _SWEEP = true;
    }




    _TICK++;
    if (false) { //exit cond.
        IO_Ctx_Flush(&_IO, PACKET_SWEEP);
        IO_Ctx_Flush(&_IO, PACKET_SENSE);
        IO_Ctx_Shutdown(&_IO);

        _LOOP = false;
        _TFINAL = millis();
    }
   
}

