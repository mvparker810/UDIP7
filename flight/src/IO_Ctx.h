#pragma once
#include <SPI.h>
#include <SD.h>
#include "stdint.h"


typedef struct IO_Ctx {
    int pin;
    char tag[32];
    char photo_path[64];

    File FILE_SWEEP;
    File FILE_SENSE;
} IO_Ctx;

typedef enum PACKET_TYPE : uint8_t {
    PACKET_SWEEP = 0,
    PACKET_SENSE = 1
} PACKET_TYPE;

typedef uint32_t pckt_timestamp;

typedef struct pckt_sense {
    pckt_timestamp TIME;

    uint16_t accel;
    uint16_t gyro;
    uint16_t magnet;
    uint16_t temperature;
} pckt_sense;
typedef struct pckt_sweep {
    pckt_timestamp TIME;
    uint16_t val; //    reading from probes
} pckt_sweep;



int IO_Ctx_Init(IO_Ctx* ctx, int SD_CS_PIN);
int IO_Ctx_WritePacket(IO_Ctx* ctx, PACKET_TYPE type, void* data);
int IO_Ctx_Flush(IO_Ctx* ctx, PACKET_TYPE type);
int IO_Ctx_Shutdown(IO_Ctx* ctx);