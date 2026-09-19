
#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

void i2c_init(void);


bool        i2c_store   (uint8_t addr, uint8_t reg, uint8_t value);
uint8_t     i2c_load    (uint8_t addr, uint8_t reg, uint8_t *buf, uint8_t len);













#ifdef __cplusplus
}
#endif
