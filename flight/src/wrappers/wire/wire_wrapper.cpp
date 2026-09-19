#include "wire_wrapper.h"

#include <Wire.h>

void i2c_init(void) {
    Wire.begin();
}

bool i2c_store(uint8_t addr, uint8_t reg, uint8_t value) {
    Wire.beginTransmission(addr);
    Wire.write(reg);
    Wire.write(value);
    return Wire.endTransmission() == 0;
}

uint8_t i2c_load(uint8_t addr, uint8_t reg, uint8_t *buf, uint8_t len) {
    Wire.beginTransmission(addr);
    Wire.write(reg);
    if (Wire.endTransmission(false) != 0) return 0;

    uint8_t received = Wire.requestFrom(addr, len);
    for (uint8_t i = 0; i < received && i < len; i++)
        buf[i] = Wire.read();
    return received;
}
