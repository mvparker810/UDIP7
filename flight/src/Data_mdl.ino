/*
DATA MODULE:

Continuously samples sensors and pushes entries into the disk ring buffer.
Never blocks: if the disk module is mid-flush and the ring is full, the entry
is dropped and counted rather than stalling sampling.
*/
#include "pin_config.h"
#include "main.h"

void Data_Init() {

}
void Data_Module(void*) {

}
