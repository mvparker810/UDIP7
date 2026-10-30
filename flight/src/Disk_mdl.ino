/*
DISK MODULE:

Drains the disk ring buffer and flushes to the drive after each batch.
Runs at a lower priority than Data, so Data keeps sampling (and filling the
ring) while a slow flush is in progress.
*/
#include "pin_config.h"
#include "main.h"

void Disk_Init() {
    //todo open SD / log file
}

void Disk_Module(void*) {
    for (;;) {
   
    }
}
