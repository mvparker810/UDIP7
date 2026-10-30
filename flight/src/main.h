#pragma once

#include <stdint.h>
#include <Arduino.h>
#include <FreeRTOS_ARM.h>
#include <utility/event_groups.h>

// X(name, stack size (in words), priority)
#define MODULES(X)          \
    X(Data,   512,  3)      \
    X(Motor,  512,  2)      \
    X(Disk,   1024, 1)

#define X(NAME, STACK, PRIO) void NAME##_Module(void *); void NAME##_Init();
MODULES(X)
#undef X

