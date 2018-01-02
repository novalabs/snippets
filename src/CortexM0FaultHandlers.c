/* COPYRIGHT (c) 2016-2018 Nova Labs SRL
 *
 * All rights reserved. All use of this software and documentation is
 * subject to the License Agreement located in the file LICENSE.
 */

#ifdef __ARM_ARCH_6M__

#include <core/snippets/CortexMxFaultHandlers.h>

#include "ch.h"

void
BusFault_Handler(
    void
) __attribute__((naked));


void
HardFault_Handler(
    void
) __attribute__((naked));


void
UsageFault_Handler(
    void
) __attribute__((naked));


void FAULT_HANDLERS_ENABLE(bool disable_write_buffer) {
}

void
BusFault_Handler(
    void
)
{
}

void
HardFault_Handler(
    void
)
{
}

void
UsageFault_Handler(
    void
)
{
}

__attribute__((used)) void
getRegistersFromStack(
    uint32_t* stack
)
{
    volatile uint32_t r0   __attribute__((unused));
    volatile uint32_t r1   __attribute__((unused));
    volatile uint32_t r2   __attribute__((unused));
    volatile uint32_t r3   __attribute__((unused));
    volatile uint32_t r12  __attribute__((unused));
    volatile uint32_t lr   __attribute__((unused));
    volatile uint32_t pc   __attribute__((unused));
    volatile uint32_t psr  __attribute__((unused));
    volatile uint32_t cfsr __attribute__((unused));

    r0  = stack[0];
    r1  = stack[1];
    r2  = stack[2];
    r3  = stack[3];
    r12 = stack[4];
    lr  = stack[5];
    pc  = stack[6];
    psr = stack[7];

    while(true) {}
} // getRegistersFromStack

#endif