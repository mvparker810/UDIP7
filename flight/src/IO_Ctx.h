#pragma once
#include <SPI.h>
#include <SD.h>
#include "stdint.h"


typedef struct IO_Ctx {
    char tag[32];
    char photo_path[64];

    File FILE_SWEEP;
    File FILE_SENSE;
} IO_Ctx; //todo make this static prob

typedef enum PACKET_TYPE : uint8_t {
    PACKET_SWEEP = 0,
    PACKET_SENSE = 1
} PACKET_TYPE;

typedef uint32_t pckt_timestamp;

//todo should i pack these
typedef struct pckt_sense {
    pckt_timestamp TIME;


    uint16_t accel  [3];
    uint16_t gyro   [3];
    uint16_t mag    [3];

    uint16_t accel_coarse;
    uint16_t temperature;
    uint16_t photo;
} pckt_sense;
typedef struct pckt_sweep {
    pckt_timestamp TIME;


    //[0] = IDK, [1] = negative
    uint16_t volt[2];

    //[0] = Probe A, [1] = Probe B
    uint16_t curr[2]; //    reading from probes
} pckt_sweep;



int IO_Ctx_Init(IO_Ctx* ctx);
int IO_Ctx_WritePacket(IO_Ctx* ctx, PACKET_TYPE type, void* data);
int IO_Ctx_Flush(IO_Ctx* ctx, PACKET_TYPE type);
int IO_Ctx_Shutdown(IO_Ctx* ctx);