#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "wrappers/wire/wire.h"

static bool _LOOP;

void setup() {
    _LOOP = true;
    i2c_init();

}




void loop() {
    if (!_LOOP) return;
}

