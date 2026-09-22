#include <SPI.h>
#include <SD.h>

typedef struct IO_Ctx {
    uint8_t v;
} IO_Ctx;

int IO_Ctx_Init(int SD_CS_PIN);

