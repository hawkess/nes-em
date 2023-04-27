#include "Bus.h"

Bus::Bus() 
{
    for (auto &idx : ram) idx = 0x00; // Initialize RAM to all 0s
}

void Bus::write(uint16_t addr, uint8_t data)
{
    if (addr >= 0x0000 && addr <= 0xFFFF) // Guard writing outside RAM range
        ram[addr] = data;
}

uint8_t Bus::read(uint16_t addr, bool readOnly = false) 
{
    if (addr >= 0x0000 && addr <= 0xFFFF) // Guard reading from RAM
        return ram[addr];
    return 0x00;
}