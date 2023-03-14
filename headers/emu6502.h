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
        uint8_t instructionData = 0x00;

        uint16_t addr_abs = 0x0000;
        uint16_t adds_rel = 0x0000;
        uint8_t curr_op = 0x00;
        uint8_t cycles = 0;


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

        std::vector<INSTRUCTION> instructionSet;


};

emu6502::emu6502()
{
    using e = emu6502;
    instructionSet = 
        {
            { "BRK", &e::BRK, &e::IMM, 7 },{ "ORA", &e::ORA, &e::IZX, 6 },{ "???", &e::XXX, &e::IMP, 2 },{ "???", &e::XXX, &e::IMP, 8 },{ "???", &e::NOP, &e::IMP, 3 },{ "ORA", &e::ORA, &e::ZPG, 3 },{ "ASL", &e::ASL, &e::ZPG, 5 },{ "???", &e::XXX, &e::IMP, 5 },{ "PHP", &e::PHP, &e::IMP, 3 },{ "ORA", &e::ORA, &e::IMM, 2 },{ "ASL", &e::ASL, &e::IMP, 2 },{ "???", &e::XXX, &e::IMP, 2 },{ "???", &e::NOP, &e::IMP, 4 },{ "ORA", &e::ORA, &e::ABS, 4 },{ "ASL", &e::ASL, &e::ABS, 6 },{ "???", &e::XXX, &e::IMP, 6 },
            { "BPL", &e::BPL, &e::REL, 2 },{ "ORA", &e::ORA, &e::IZY, 5 },{ "???", &e::XXX, &e::IMP, 2 },{ "???", &e::XXX, &e::IMP, 8 },{ "???", &e::NOP, &e::IMP, 4 },{ "ORA", &e::ORA, &e::ZPX, 4 },{ "ASL", &e::ASL, &e::ZPX, 6 },{ "???", &e::XXX, &e::IMP, 6 },{ "CLC", &e::CLC, &e::IMP, 2 },{ "ORA", &e::ORA, &e::ABY, 4 },{ "???", &e::NOP, &e::IMP, 2 },{ "???", &e::XXX, &e::IMP, 7 },{ "???", &e::NOP, &e::IMP, 4 },{ "ORA", &e::ORA, &e::ABX, 4 },{ "ASL", &e::ASL, &e::ABX, 7 },{ "???", &e::XXX, &e::IMP, 7 },
            { "JSR", &e::JSR, &e::ABS, 6 },{ "AND", &e::AND, &e::IZX, 6 },{ "???", &e::XXX, &e::IMP, 2 },{ "???", &e::XXX, &e::IMP, 8 },{ "BIT", &e::BIT, &e::ZPG, 3 },{ "AND", &e::AND, &e::ZPG, 3 },{ "ROL", &e::ROL, &e::ZPG, 5 },{ "???", &e::XXX, &e::IMP, 5 },{ "PLP", &e::PLP, &e::IMP, 4 },{ "AND", &e::AND, &e::IMM, 2 },{ "ROL", &e::ROL, &e::IMP, 2 },{ "???", &e::XXX, &e::IMP, 2 },{ "BIT", &e::BIT, &e::ABS, 4 },{ "AND", &e::AND, &e::ABS, 4 },{ "ROL", &e::ROL, &e::ABS, 6 },{ "???", &e::XXX, &e::IMP, 6 },
            { "BMI", &e::BMI, &e::REL, 2 },{ "AND", &e::AND, &e::IZY, 5 },{ "???", &e::XXX, &e::IMP, 2 },{ "???", &e::XXX, &e::IMP, 8 },{ "???", &e::NOP, &e::IMP, 4 },{ "AND", &e::AND, &e::ZPX, 4 },{ "ROL", &e::ROL, &e::ZPX, 6 },{ "???", &e::XXX, &e::IMP, 6 },{ "SEC", &e::SEC, &e::IMP, 2 },{ "AND", &e::AND, &e::ABY, 4 },{ "???", &e::NOP, &e::IMP, 2 },{ "???", &e::XXX, &e::IMP, 7 },{ "???", &e::NOP, &e::IMP, 4 },{ "AND", &e::AND, &e::ABX, 4 },{ "ROL", &e::ROL, &e::ABX, 7 },{ "???", &e::XXX, &e::IMP, 7 },
            { "RTI", &e::RTI, &e::IMP, 6 },{ "EOR", &e::EOR, &e::IZX, 6 },{ "???", &e::XXX, &e::IMP, 2 },{ "???", &e::XXX, &e::IMP, 8 },{ "???", &e::NOP, &e::IMP, 3 },{ "EOR", &e::EOR, &e::ZPG, 3 },{ "LSR", &e::LSR, &e::ZPG, 5 },{ "???", &e::XXX, &e::IMP, 5 },{ "PHA", &e::PHA, &e::IMP, 3 },{ "EOR", &e::EOR, &e::IMM, 2 },{ "LSR", &e::LSR, &e::IMP, 2 },{ "???", &e::XXX, &e::IMP, 2 },{ "JMP", &e::JMP, &e::ABS, 3 },{ "EOR", &e::EOR, &e::ABS, 4 },{ "LSR", &e::LSR, &e::ABS, 6 },{ "???", &e::XXX, &e::IMP, 6 },
            { "BVC", &e::BVC, &e::REL, 2 },{ "EOR", &e::EOR, &e::IZY, 5 },{ "???", &e::XXX, &e::IMP, 2 },{ "???", &e::XXX, &e::IMP, 8 },{ "???", &e::NOP, &e::IMP, 4 },{ "EOR", &e::EOR, &e::ZPX, 4 },{ "LSR", &e::LSR, &e::ZPX, 6 },{ "???", &e::XXX, &e::IMP, 6 },{ "CLI", &e::CLI, &e::IMP, 2 },{ "EOR", &e::EOR, &e::ABY, 4 },{ "???", &e::NOP, &e::IMP, 2 },{ "???", &e::XXX, &e::IMP, 7 },{ "???", &e::NOP, &e::IMP, 4 },{ "EOR", &e::EOR, &e::ABX, 4 },{ "LSR", &e::LSR, &e::ABX, 7 },{ "???", &e::XXX, &e::IMP, 7 },
            { "RTS", &e::RTS, &e::IMP, 6 },{ "ADC", &e::ADC, &e::IZX, 6 },{ "???", &e::XXX, &e::IMP, 2 },{ "???", &e::XXX, &e::IMP, 8 },{ "???", &e::NOP, &e::IMP, 3 },{ "ADC", &e::ADC, &e::ZPG, 3 },{ "ROR", &e::ROR, &e::ZPG, 5 },{ "???", &e::XXX, &e::IMP, 5 },{ "PLA", &e::PLA, &e::IMP, 4 },{ "ADC", &e::ADC, &e::IMM, 2 },{ "ROR", &e::ROR, &e::IMP, 2 },{ "???", &e::XXX, &e::IMP, 2 },{ "JMP", &e::JMP, &e::IZX, 5 },{ "ADC", &e::ADC, &e::ABS, 4 },{ "ROR", &e::ROR, &e::ABS, 6 },{ "???", &e::XXX, &e::IMP, 6 },
            { "BVS", &e::BVS, &e::REL, 2 },{ "ADC", &e::ADC, &e::IZY, 5 },{ "???", &e::XXX, &e::IMP, 2 },{ "???", &e::XXX, &e::IMP, 8 },{ "???", &e::NOP, &e::IMP, 4 },{ "ADC", &e::ADC, &e::ZPX, 4 },{ "ROR", &e::ROR, &e::ZPX, 6 },{ "???", &e::XXX, &e::IMP, 6 },{ "SEI", &e::SEI, &e::IMP, 2 },{ "ADC", &e::ADC, &e::ABY, 4 },{ "???", &e::NOP, &e::IMP, 2 },{ "???", &e::XXX, &e::IMP, 7 },{ "???", &e::NOP, &e::IMP, 4 },{ "ADC", &e::ADC, &e::ABX, 4 },{ "ROR", &e::ROR, &e::ABX, 7 },{ "???", &e::XXX, &e::IMP, 7 },
            { "???", &e::NOP, &e::IMP, 2 },{ "STA", &e::STA, &e::IZX, 6 },{ "???", &e::NOP, &e::IMP, 2 },{ "???", &e::XXX, &e::IMP, 6 },{ "STY", &e::STY, &e::ZPG, 3 },{ "STA", &e::STA, &e::ZPG, 3 },{ "STX", &e::STX, &e::ZPG, 3 },{ "???", &e::XXX, &e::IMP, 3 },{ "DEY", &e::DEY, &e::IMP, 2 },{ "???", &e::NOP, &e::IMP, 2 },{ "TXA", &e::TXA, &e::IMP, 2 },{ "???", &e::XXX, &e::IMP, 2 },{ "STY", &e::STY, &e::ABS, 4 },{ "STA", &e::STA, &e::ABS, 4 },{ "STX", &e::STX, &e::ABS, 4 },{ "???", &e::XXX, &e::IMP, 4 },
            { "BCC", &e::BCC, &e::REL, 2 },{ "STA", &e::STA, &e::IZY, 6 },{ "???", &e::XXX, &e::IMP, 2 },{ "???", &e::XXX, &e::IMP, 6 },{ "STY", &e::STY, &e::ZPX, 4 },{ "STA", &e::STA, &e::ZPX, 4 },{ "STX", &e::STX, &e::ZPY, 4 },{ "???", &e::XXX, &e::IMP, 4 },{ "TYA", &e::TYA, &e::IMP, 2 },{ "STA", &e::STA, &e::ABY, 5 },{ "TXS", &e::TXS, &e::IMP, 2 },{ "???", &e::XXX, &e::IMP, 5 },{ "???", &e::NOP, &e::IMP, 5 },{ "STA", &e::STA, &e::ABX, 5 },{ "???", &e::XXX, &e::IMP, 5 },{ "???", &e::XXX, &e::IMP, 5 },
            { "LDY", &e::LDY, &e::IMM, 2 },{ "LDA", &e::LDA, &e::IZX, 6 },{ "LDX", &e::LDX, &e::IMM, 2 },{ "???", &e::XXX, &e::IMP, 6 },{ "LDY", &e::LDY, &e::ZPG, 3 },{ "LDA", &e::LDA, &e::ZPG, 3 },{ "LDX", &e::LDX, &e::ZPG, 3 },{ "???", &e::XXX, &e::IMP, 3 },{ "TAY", &e::TAY, &e::IMP, 2 },{ "LDA", &e::LDA, &e::IMM, 2 },{ "TAX", &e::TAX, &e::IMP, 2 },{ "???", &e::XXX, &e::IMP, 2 },{ "LDY", &e::LDY, &e::ABS, 4 },{ "LDA", &e::LDA, &e::ABS, 4 },{ "LDX", &e::LDX, &e::ABS, 4 },{ "???", &e::XXX, &e::IMP, 4 },
            { "BCS", &e::BCS, &e::REL, 2 },{ "LDA", &e::LDA, &e::IZY, 5 },{ "???", &e::XXX, &e::IMP, 2 },{ "???", &e::XXX, &e::IMP, 5 },{ "LDY", &e::LDY, &e::ZPX, 4 },{ "LDA", &e::LDA, &e::ZPX, 4 },{ "LDX", &e::LDX, &e::ZPY, 4 },{ "???", &e::XXX, &e::IMP, 4 },{ "CLV", &e::CLV, &e::IMP, 2 },{ "LDA", &e::LDA, &e::ABY, 4 },{ "TSX", &e::TSX, &e::IMP, 2 },{ "???", &e::XXX, &e::IMP, 4 },{ "LDY", &e::LDY, &e::ABX, 4 },{ "LDA", &e::LDA, &e::ABX, 4 },{ "LDX", &e::LDX, &e::ABY, 4 },{ "???", &e::XXX, &e::IMP, 4 },
            { "CPY", &e::CPY, &e::IMM, 2 },{ "CMP", &e::CMP, &e::IZX, 6 },{ "???", &e::NOP, &e::IMP, 2 },{ "???", &e::XXX, &e::IMP, 8 },{ "CPY", &e::CPY, &e::ZPG, 3 },{ "CMP", &e::CMP, &e::ZPG, 3 },{ "DEC", &e::DEC, &e::ZPG, 5 },{ "???", &e::XXX, &e::IMP, 5 },{ "INY", &e::INY, &e::IMP, 2 },{ "CMP", &e::CMP, &e::IMM, 2 },{ "DEX", &e::DEX, &e::IMP, 2 },{ "???", &e::XXX, &e::IMP, 2 },{ "CPY", &e::CPY, &e::ABS, 4 },{ "CMP", &e::CMP, &e::ABS, 4 },{ "DEC", &e::DEC, &e::ABS, 6 },{ "???", &e::XXX, &e::IMP, 6 },
            { "BNE", &e::BNE, &e::REL, 2 },{ "CMP", &e::CMP, &e::IZY, 5 },{ "???", &e::XXX, &e::IMP, 2 },{ "???", &e::XXX, &e::IMP, 8 },{ "???", &e::NOP, &e::IMP, 4 },{ "CMP", &e::CMP, &e::ZPX, 4 },{ "DEC", &e::DEC, &e::ZPX, 6 },{ "???", &e::XXX, &e::IMP, 6 },{ "CLD", &e::CLD, &e::IMP, 2 },{ "CMP", &e::CMP, &e::ABY, 4 },{ "NOP", &e::NOP, &e::IMP, 2 },{ "???", &e::XXX, &e::IMP, 7 },{ "???", &e::NOP, &e::IMP, 4 },{ "CMP", &e::CMP, &e::ABX, 4 },{ "DEC", &e::DEC, &e::ABX, 7 },{ "???", &e::XXX, &e::IMP, 7 },
            { "CPX", &e::CPX, &e::IMM, 2 },{ "SBC", &e::SBC, &e::IZX, 6 },{ "???", &e::NOP, &e::IMP, 2 },{ "???", &e::XXX, &e::IMP, 8 },{ "CPX", &e::CPX, &e::ZPG, 3 },{ "SBC", &e::SBC, &e::ZPG, 3 },{ "INC", &e::INC, &e::ZPG, 5 },{ "???", &e::XXX, &e::IMP, 5 },{ "INX", &e::INX, &e::IMP, 2 },{ "SBC", &e::SBC, &e::IMM, 2 },{ "NOP", &e::NOP, &e::IMP, 2 },{ "???", &e::SBC, &e::IMP, 2 },{ "CPX", &e::CPX, &e::ABS, 4 },{ "SBC", &e::SBC, &e::ABS, 4 },{ "INC", &e::INC, &e::ABS, 6 },{ "???", &e::XXX, &e::IMP, 6 },
            { "BEQ", &e::BEQ, &e::REL, 2 },{ "SBC", &e::SBC, &e::IZY, 5 },{ "???", &e::XXX, &e::IMP, 2 },{ "???", &e::XXX, &e::IMP, 8 },{ "???", &e::NOP, &e::IMP, 4 },{ "SBC", &e::SBC, &e::ZPX, 4 },{ "INC", &e::INC, &e::ZPX, 6 },{ "???", &e::XXX, &e::IMP, 6 },{ "SED", &e::SED, &e::IMP, 2 },{ "SBC", &e::SBC, &e::ABY, 4 },{ "NOP", &e::NOP, &e::IMP, 2 },{ "???", &e::XXX, &e::IMP, 7 },{ "???", &e::NOP, &e::IMP, 4 },{ "SBC", &e::SBC, &e::ABX, 4 },{ "INC", &e::INC, &e::ABX, 7 },{ "???", &e::XXX, &e::IMP, 7 },
        };
}

emu6502::~emu6502()
{

}

uint8_t emu6502::getStatusFlag(STATUS_FLAGS f)
{

}

void emu6502::setStatusFlag(STATUS_FLAGS f, bool v)
{

}

uint8_t emu6502::read(uint16_t addr)
{
    return bus->read(addr);
}

void emu6502::write(uint16_t addr, uint8_t data)
{
    bus->write(addr, data);
}

#endif