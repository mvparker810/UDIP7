#include <SPI.h>
#include <SD.h>
#include <Arduino.h>
#include "IO_Ctx.h"
#include "stdint.h"

static uint32_t random_32() {
    static bool init = false;
    if (!init) {
        pmc_enable_periph_clk(ID_TRNG);
        REG_TRNG_CR = TRNG_CR_KEY(0x524E47) | TRNG_CR_ENABLE;
        init = true;
    }
    while (!(REG_TRNG_ISR & TRNG_ISR_DATRDY)) {}
    return REG_TRNG_ODATA;
}

int IO_Ctx_Init(IO_Ctx* ctx, int pin) {
    ctx->pin = pin;
    if (!SD.begin(pin)) {
        return -1; //todo extensive error logging/handling
    }

    const char charset[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-_";
    size_t tagLen = sizeof(ctx->tag);
    for (size_t i = 0; i < tagLen - 1; i++)
        ctx->tag[i] = charset[random_32() % (sizeof(charset) - 1)];
    ctx->tag[tagLen - 1] = '\0';

    //make the directory. todo should probably check for name collisions, even if its statistically impossible.
    if (!SD.mkdir(ctx->tag)) {
        return -1; //tood more error logs
    }

    sprintf(ctx->photo_path, "%s/capture", ctx->tag);
    if (!SD.mkdir(ctx->photo_path)) {
        return -1; //tood more error logs
    }

    char temp[64];
    sprintf(temp, "%s/sweep", ctx->tag);
    ctx->FILE_SENSE = SD.open(temp, FILE_WRITE);
    if (!ctx->FILE_SENSE) {
        return -1; //ditto
    }

    sprintf(temp, "%s/sweep", ctx->tag);
    ctx->FILE_SWEEP = SD.open(temp, FILE_WRITE);
    if (!ctx->FILE_SWEEP) {
        return -1; //ditto
    }



    return 0;
}

int IO_Ctx_WriteImage(IO_Ctx* ctx) {
    //assert(false); //todo
}

int IO_Ctx_WritePacket(IO_Ctx* ctx, PACKET_TYPE type, void* data) {
    if (type == PACKET_SENSE) {
        pckt_sense* pckt = (pckt_sense*)data;
        ctx->FILE_SENSE.write((uint8_t*)pckt, sizeof(pckt_sense));
        return 0;
    }
    if (type == PACKET_SWEEP) {
        pckt_sweep* pckt = (pckt_sweep*)data;
        ctx->FILE_SWEEP.write((uint8_t*)pckt, sizeof(pckt_sweep));
        return 0;
    }

    return -1;
}


int IO_Ctx_Flush(IO_Ctx* ctx, PACKET_TYPE type) {
    if (type == PACKET_SENSE)   {
        ctx->FILE_SENSE.flush();
        return 0;
    }
    if (type == PACKET_SWEEP) {
        ctx->FILE_SWEEP.flush();
        return 0;
    }  

    return -1;
}


int IO_Ctx_Shutdown(IO_Ctx* ctx) {
    ctx->FILE_SENSE.close();
    ctx->FILE_SWEEP.close();
    
}