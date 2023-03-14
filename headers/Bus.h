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

Bus::Bus() 
{
    for (auto &idx : ram) idx = 0x00;
}

void Bus::write(uint16_t addr, uint8_t data)
{
    if (addr >= 0x0000 && addr <= 0xFFFF)
        ram[addr] = data;
}

uint8_t Bus::read(uint16_t addr, bool readOnly = false) 
{
    if (addr >= 0x0000 && addr <= 0xFFFF)
        return ram[addr];
    return 0x00;
}


#endif