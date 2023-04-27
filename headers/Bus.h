#ifndef BUS_H
#define BUS_H
#pragma once
#include <cstdint>
#include "emu6502.h"
#include <array>

class Bus 
{
    public:
        Bus();
        ~Bus();

        void write(uint16_t addr, uint8_t data);
        uint8_t read(uint16_t addr, bool readOnly = false);

        //emulated devices on bus;
        emu6502 cpu;
        std::array<uint8_t, 64 * 1024> ram;
};

#endif