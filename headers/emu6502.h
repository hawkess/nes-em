#ifndef EMU6502_H
#define EMU6502_H
#pragma once
#include <cstdint>
#include <string>
#include <vector>
#include "Bus.h"

class Bus;

class emu6502
{
    public:
        emu6502();
        ~emu6502();

        void connectToBus(Bus* n) { bus = n; }

        enum STATUS_FLAGS
        {
            C = (1 << 0), // Carry
            Z = (1 << 1), // Zero result
            I = (1 << 2), // IRQ disable
            D = (1 << 3), // Decimal mode
            B = (1 << 4), // BRK command
            U = (1 << 5), // unused bit
            V = (1 << 6), // Overflow
            N = (1 << 7), // Negative
        };

        // Registers
        uint8_t a = 0x00; // Accumulator
        uint8_t x = 0x00; // X
        uint8_t y = 0x00; // Y
        uint8_t sta = 0x00; // Status
        uint8_t stkp = 0x00; // Stack pointer
        uint16_t pc = 0x0000; // Program counter

        // Addressing modes
        uint8_t IMP(); // Implied
        uint8_t ACC(); // Accumulator
        uint8_t IMM(); // Immediate
        uint8_t ABS(); // Absolute
        uint8_t ZPG(); // Zero Page 
        uint8_t ABX(); // Absolute Indexed X (ABS, X)
        uint8_t ABY(); // Absolute Indexed Y (ABS, Y)
        uint8_t ZPX(); // Zero Page Indexed X (ZPG, X)
        uint8_t ZPY(); // Zero Page Indexed Y (ZPG, Y)
        uint8_t REL(); // Relative
        uint8_t IZX(); // Zero Page Indexed Indirect [(IND, X)]
        uint8_t AIX(); // *Absolute Indexed Indirect [ABS(IND, X)]      (Jump only)
        uint8_t IZY(); // Indirect Indexed [(IND, Y)]
        uint8_t ZIA(); // *Zero Page Indirect [(ZPG)]                   (Jump only)
        uint8_t AIA(); // *Absolute Indirect [(ABS)]                    (Jump only)

        //Op codes
        uint8_t ADC();        uint8_t AND();
        uint8_t ASL();        uint8_t BCC();
        uint8_t BCS();        uint8_t BEQ();
        uint8_t BIT();        uint8_t BMI();
        uint8_t BNE();        uint8_t BPL();
        uint8_t BRA();        uint8_t BRK();
        uint8_t BVC();        uint8_t BVS();
        uint8_t CLC();        uint8_t CLD();
        uint8_t CLI();        uint8_t CLV();
        uint8_t CMP();        uint8_t CPX();
        uint8_t CPY();        uint8_t DEA();
        uint8_t DEC();        uint8_t DEX();
        uint8_t DEY();        uint8_t EOR();
        uint8_t INA();        uint8_t INC();
        uint8_t INX();        uint8_t INY();
        uint8_t JMP();        uint8_t JSR();
        uint8_t LDA();        uint8_t LDX();
        uint8_t LDY();        uint8_t LSR();
        uint8_t NOP();        uint8_t ORA();
        uint8_t PHA();        uint8_t PHP();
        uint8_t PHX();        uint8_t PHY();
        uint8_t PLA();        uint8_t PLP();
        uint8_t PLX();        uint8_t PLY();
        uint8_t ROL();        uint8_t ROR();
        uint8_t RTI();        uint8_t RTS();
        uint8_t SBC();        uint8_t SEC();
        uint8_t SED();        uint8_t SEI();
        uint8_t STA();        uint8_t STX();
        uint8_t STY();        uint8_t STZ();
        uint8_t TAX();        uint8_t TAY();
        uint8_t TRB();        uint8_t TSB();
        uint8_t TSX();        uint8_t TXA();
        uint8_t TXS();        uint8_t TYA();
        uint8_t XXX(); // Illegal op code catchall

        // Signals
        void cycle();
        void reset();
        void irq();
        void nmi();
        
        // Helpers
        uint8_t getInstructionData();
        uint8_t instruction_data = 0x00;
        uint16_t temp = 0x0000;
        uint16_t addr_abs = 0x0000;
        uint16_t adds_rel = 0x0000;
        uint8_t curr_op = 0x00;
        uint8_t cycles = 0;
        uint32_t clock_count = 0;


    private:
        Bus *bus = nullptr;
        uint8_t getStatusFlag(STATUS_FLAGS f);
        void setStatusFlag(STATUS_FLAGS f, bool v);
        uint8_t read(uint16_t addr);
        void write(uint16_t addr, uint8_t data);

        struct INSTRUCTION 
        {
            std::string name;
            uint8_t (emu6502::*addr_mode)(void) = nullptr;
            uint8_t (emu6502::*operation)(void) = nullptr;
            uint8_t cycles = 0;
        };

        std::vector<INSTRUCTION> instruction_set;


};

#endif