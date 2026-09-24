#include <stdint.h>

typedef enum MOTORSTATE : uint8_t {
    MOTORSTATE_DEPLOYED,
    MOTORSTATE_RETRACT
} MOTORSTATE;


int MotorCtx_Init();
int MotorCtx_Poll(uint32_t time);
int MotorCtx_SetState(MOTORSTATE state);