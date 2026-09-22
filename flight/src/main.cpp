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

Due can read pins 0-4095

*/

//in seconds.todo should probably thow these in ms
#define LANDMARK_TE1 80
#define LANDMARK_TE2 322
#define LANDMARK_POWOFF 332

#define PACKET_LOG_DELAY_MS 10      //how periodically do we measure and write a packet in ms
#define PACKET_FLUSH 25             //how many cycles of logging until we flush to the drive


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
    IO_Ctx_Init(&_IO, -1); //TODO what will the pin be

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
        bool flush = (!(packet_last_ms % PACKET_FLUSH));
         //todo is flushing when no data ok?

        if (_SWEEP) {
            pckt_sweep PCKT = {NOW};
            //todo measeure sweep data. write to struct
            IO_Ctx_WritePacket(&_IO, PACKET_SWEEP, (void*)&PCKT);
            if (flush) IO_Ctx_Flush(&_IO, PACKET_SWEEP);
        }
        {
            pckt_sense PCKT = {NOW};
            //todo measeure sensor data. write to struct
            IO_Ctx_WritePacket(&_IO, PACKET_SENSE, (void*)&PCKT);
            if (flush) IO_Ctx_Flush(&_IO, PACKET_SENSE);
        }
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

