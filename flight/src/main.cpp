#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include <Wire.h>
#include <SPI.h>
#include <SD.h>

#include "IO_Ctx.h"

//in seconds.todo should probably thow these in ms
#define LANDMARK_TE1 80
#define LANDMARK_TE2 322
#define LANDMARK_POWOFF 332

typedef struct pckt_sense {
    uint8_t v;
} pckt_sense;
typedef struct pckt_sweep {
    uint8_t v;
} pckt_sweep;


// ====================



static bool     _LOOP;
static IO_Ctx   _IO;
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

    //_FILE = fopen("");

    _TINIT = millis(); _TFINAL = 0;
    _TICK = 0;
}


 

void loop() {
    if (!_LOOP) return;
    uint32_t T_PLUS_MS = millis() - _TINIT;

    static bool _SWEEP = false; //todo this is checked by an input pin i presume
    static uint32_t packet_status = 0;







    _TICK++;
    if (false) { //exit cond. 
        _LOOP = false;
        _TFINAL = millis();
    }
   
}

