#include "emu6502.h"

emu6502::emu6502()
{
    using e = emu6502;
    instruction_set = 
        {
            { "BRK", &e::BRK, &e::IMM, 7 },{ "ORA", &e::ORA, &e::IZX, 6 },{ "___", &e::XXX, &e::IMP, 2 },{ "___", &e::XXX, &e::IMP, 8 },{ "___", &e::NOP, &e::IMP, 3 },{ "ORA", &e::ORA, &e::ZPG, 3 },{ "ASL", &e::ASL, &e::ZPG, 5 },{ "___", &e::XXX, &e::IMP, 5 },{ "PHP", &e::PHP, &e::IMP, 3 },{ "ORA", &e::ORA, &e::IMM, 2 },{ "ASL", &e::ASL, &e::IMP, 2 },{ "___", &e::XXX, &e::IMP, 2 },{ "___", &e::NOP, &e::IMP, 4 },{ "ORA", &e::ORA, &e::ABS, 4 },{ "ASL", &e::ASL, &e::ABS, 6 },{ "___", &e::XXX, &e::IMP, 6 },
            { "BPL", &e::BPL, &e::REL, 2 },{ "ORA", &e::ORA, &e::IZY, 5 },{ "___", &e::XXX, &e::IMP, 2 },{ "___", &e::XXX, &e::IMP, 8 },{ "___", &e::NOP, &e::IMP, 4 },{ "ORA", &e::ORA, &e::ZPX, 4 },{ "ASL", &e::ASL, &e::ZPX, 6 },{ "___", &e::XXX, &e::IMP, 6 },{ "CLC", &e::CLC, &e::IMP, 2 },{ "ORA", &e::ORA, &e::ABY, 4 },{ "___", &e::NOP, &e::IMP, 2 },{ "___", &e::XXX, &e::IMP, 7 },{ "___", &e::NOP, &e::IMP, 4 },{ "ORA", &e::ORA, &e::ABX, 4 },{ "ASL", &e::ASL, &e::ABX, 7 },{ "___", &e::XXX, &e::IMP, 7 },
            { "JSR", &e::JSR, &e::ABS, 6 },{ "AND", &e::AND, &e::IZX, 6 },{ "___", &e::XXX, &e::IMP, 2 },{ "___", &e::XXX, &e::IMP, 8 },{ "BIT", &e::BIT, &e::ZPG, 3 },{ "AND", &e::AND, &e::ZPG, 3 },{ "ROL", &e::ROL, &e::ZPG, 5 },{ "___", &e::XXX, &e::IMP, 5 },{ "PLP", &e::PLP, &e::IMP, 4 },{ "AND", &e::AND, &e::IMM, 2 },{ "ROL", &e::ROL, &e::IMP, 2 },{ "___", &e::XXX, &e::IMP, 2 },{ "BIT", &e::BIT, &e::ABS, 4 },{ "AND", &e::AND, &e::ABS, 4 },{ "ROL", &e::ROL, &e::ABS, 6 },{ "___", &e::XXX, &e::IMP, 6 },
            { "BMI", &e::BMI, &e::REL, 2 },{ "AND", &e::AND, &e::IZY, 5 },{ "___", &e::XXX, &e::IMP, 2 },{ "___", &e::XXX, &e::IMP, 8 },{ "___", &e::NOP, &e::IMP, 4 },{ "AND", &e::AND, &e::ZPX, 4 },{ "ROL", &e::ROL, &e::ZPX, 6 },{ "___", &e::XXX, &e::IMP, 6 },{ "SEC", &e::SEC, &e::IMP, 2 },{ "AND", &e::AND, &e::ABY, 4 },{ "___", &e::NOP, &e::IMP, 2 },{ "___", &e::XXX, &e::IMP, 7 },{ "___", &e::NOP, &e::IMP, 4 },{ "AND", &e::AND, &e::ABX, 4 },{ "ROL", &e::ROL, &e::ABX, 7 },{ "___", &e::XXX, &e::IMP, 7 },
            { "RTI", &e::RTI, &e::IMP, 6 },{ "EOR", &e::EOR, &e::IZX, 6 },{ "___", &e::XXX, &e::IMP, 2 },{ "___", &e::XXX, &e::IMP, 8 },{ "___", &e::NOP, &e::IMP, 3 },{ "EOR", &e::EOR, &e::ZPG, 3 },{ "LSR", &e::LSR, &e::ZPG, 5 },{ "___", &e::XXX, &e::IMP, 5 },{ "PHA", &e::PHA, &e::IMP, 3 },{ "EOR", &e::EOR, &e::IMM, 2 },{ "LSR", &e::LSR, &e::IMP, 2 },{ "___", &e::XXX, &e::IMP, 2 },{ "JMP", &e::JMP, &e::ABS, 3 },{ "EOR", &e::EOR, &e::ABS, 4 },{ "LSR", &e::LSR, &e::ABS, 6 },{ "___", &e::XXX, &e::IMP, 6 },
            { "BVC", &e::BVC, &e::REL, 2 },{ "EOR", &e::EOR, &e::IZY, 5 },{ "___", &e::XXX, &e::IMP, 2 },{ "___", &e::XXX, &e::IMP, 8 },{ "___", &e::NOP, &e::IMP, 4 },{ "EOR", &e::EOR, &e::ZPX, 4 },{ "LSR", &e::LSR, &e::ZPX, 6 },{ "___", &e::XXX, &e::IMP, 6 },{ "CLI", &e::CLI, &e::IMP, 2 },{ "EOR", &e::EOR, &e::ABY, 4 },{ "___", &e::NOP, &e::IMP, 2 },{ "___", &e::XXX, &e::IMP, 7 },{ "___", &e::NOP, &e::IMP, 4 },{ "EOR", &e::EOR, &e::ABX, 4 },{ "LSR", &e::LSR, &e::ABX, 7 },{ "___", &e::XXX, &e::IMP, 7 },
            { "RTS", &e::RTS, &e::IMP, 6 },{ "ADC", &e::ADC, &e::IZX, 6 },{ "___", &e::XXX, &e::IMP, 2 },{ "___", &e::XXX, &e::IMP, 8 },{ "___", &e::NOP, &e::IMP, 3 },{ "ADC", &e::ADC, &e::ZPG, 3 },{ "ROR", &e::ROR, &e::ZPG, 5 },{ "___", &e::XXX, &e::IMP, 5 },{ "PLA", &e::PLA, &e::IMP, 4 },{ "ADC", &e::ADC, &e::IMM, 2 },{ "ROR", &e::ROR, &e::IMP, 2 },{ "___", &e::XXX, &e::IMP, 2 },{ "JMP", &e::JMP, &e::IZX, 5 },{ "ADC", &e::ADC, &e::ABS, 4 },{ "ROR", &e::ROR, &e::ABS, 6 },{ "___", &e::XXX, &e::IMP, 6 },
            { "BVS", &e::BVS, &e::REL, 2 },{ "ADC", &e::ADC, &e::IZY, 5 },{ "___", &e::XXX, &e::IMP, 2 },{ "___", &e::XXX, &e::IMP, 8 },{ "___", &e::NOP, &e::IMP, 4 },{ "ADC", &e::ADC, &e::ZPX, 4 },{ "ROR", &e::ROR, &e::ZPX, 6 },{ "___", &e::XXX, &e::IMP, 6 },{ "SEI", &e::SEI, &e::IMP, 2 },{ "ADC", &e::ADC, &e::ABY, 4 },{ "___", &e::NOP, &e::IMP, 2 },{ "___", &e::XXX, &e::IMP, 7 },{ "___", &e::NOP, &e::IMP, 4 },{ "ADC", &e::ADC, &e::ABX, 4 },{ "ROR", &e::ROR, &e::ABX, 7 },{ "___", &e::XXX, &e::IMP, 7 },
            { "___", &e::NOP, &e::IMP, 2 },{ "STA", &e::STA, &e::IZX, 6 },{ "___", &e::NOP, &e::IMP, 2 },{ "___", &e::XXX, &e::IMP, 6 },{ "STY", &e::STY, &e::ZPG, 3 },{ "STA", &e::STA, &e::ZPG, 3 },{ "STX", &e::STX, &e::ZPG, 3 },{ "___", &e::XXX, &e::IMP, 3 },{ "DEY", &e::DEY, &e::IMP, 2 },{ "___", &e::NOP, &e::IMP, 2 },{ "TXA", &e::TXA, &e::IMP, 2 },{ "___", &e::XXX, &e::IMP, 2 },{ "STY", &e::STY, &e::ABS, 4 },{ "STA", &e::STA, &e::ABS, 4 },{ "STX", &e::STX, &e::ABS, 4 },{ "___", &e::XXX, &e::IMP, 4 },
            { "BCC", &e::BCC, &e::REL, 2 },{ "STA", &e::STA, &e::IZY, 6 },{ "___", &e::XXX, &e::IMP, 2 },{ "___", &e::XXX, &e::IMP, 6 },{ "STY", &e::STY, &e::ZPX, 4 },{ "STA", &e::STA, &e::ZPX, 4 },{ "STX", &e::STX, &e::ZPY, 4 },{ "___", &e::XXX, &e::IMP, 4 },{ "TYA", &e::TYA, &e::IMP, 2 },{ "STA", &e::STA, &e::ABY, 5 },{ "TXS", &e::TXS, &e::IMP, 2 },{ "___", &e::XXX, &e::IMP, 5 },{ "___", &e::NOP, &e::IMP, 5 },{ "STA", &e::STA, &e::ABX, 5 },{ "___", &e::XXX, &e::IMP, 5 },{ "___", &e::XXX, &e::IMP, 5 },
            { "LDY", &e::LDY, &e::IMM, 2 },{ "LDA", &e::LDA, &e::IZX, 6 },{ "LDX", &e::LDX, &e::IMM, 2 },{ "___", &e::XXX, &e::IMP, 6 },{ "LDY", &e::LDY, &e::ZPG, 3 },{ "LDA", &e::LDA, &e::ZPG, 3 },{ "LDX", &e::LDX, &e::ZPG, 3 },{ "___", &e::XXX, &e::IMP, 3 },{ "TAY", &e::TAY, &e::IMP, 2 },{ "LDA", &e::LDA, &e::IMM, 2 },{ "TAX", &e::TAX, &e::IMP, 2 },{ "___", &e::XXX, &e::IMP, 2 },{ "LDY", &e::LDY, &e::ABS, 4 },{ "LDA", &e::LDA, &e::ABS, 4 },{ "LDX", &e::LDX, &e::ABS, 4 },{ "___", &e::XXX, &e::IMP, 4 },
            { "BCS", &e::BCS, &e::REL, 2 },{ "LDA", &e::LDA, &e::IZY, 5 },{ "___", &e::XXX, &e::IMP, 2 },{ "___", &e::XXX, &e::IMP, 5 },{ "LDY", &e::LDY, &e::ZPX, 4 },{ "LDA", &e::LDA, &e::ZPX, 4 },{ "LDX", &e::LDX, &e::ZPY, 4 },{ "___", &e::XXX, &e::IMP, 4 },{ "CLV", &e::CLV, &e::IMP, 2 },{ "LDA", &e::LDA, &e::ABY, 4 },{ "TSX", &e::TSX, &e::IMP, 2 },{ "___", &e::XXX, &e::IMP, 4 },{ "LDY", &e::LDY, &e::ABX, 4 },{ "LDA", &e::LDA, &e::ABX, 4 },{ "LDX", &e::LDX, &e::ABY, 4 },{ "___", &e::XXX, &e::IMP, 4 },
            { "CPY", &e::CPY, &e::IMM, 2 },{ "CMP", &e::CMP, &e::IZX, 6 },{ "___", &e::NOP, &e::IMP, 2 },{ "___", &e::XXX, &e::IMP, 8 },{ "CPY", &e::CPY, &e::ZPG, 3 },{ "CMP", &e::CMP, &e::ZPG, 3 },{ "DEC", &e::DEC, &e::ZPG, 5 },{ "___", &e::XXX, &e::IMP, 5 },{ "INY", &e::INY, &e::IMP, 2 },{ "CMP", &e::CMP, &e::IMM, 2 },{ "DEX", &e::DEX, &e::IMP, 2 },{ "___", &e::XXX, &e::IMP, 2 },{ "CPY", &e::CPY, &e::ABS, 4 },{ "CMP", &e::CMP, &e::ABS, 4 },{ "DEC", &e::DEC, &e::ABS, 6 },{ "___", &e::XXX, &e::IMP, 6 },
            { "BNE", &e::BNE, &e::REL, 2 },{ "CMP", &e::CMP, &e::IZY, 5 },{ "___", &e::XXX, &e::IMP, 2 },{ "___", &e::XXX, &e::IMP, 8 },{ "___", &e::NOP, &e::IMP, 4 },{ "CMP", &e::CMP, &e::ZPX, 4 },{ "DEC", &e::DEC, &e::ZPX, 6 },{ "___", &e::XXX, &e::IMP, 6 },{ "CLD", &e::CLD, &e::IMP, 2 },{ "CMP", &e::CMP, &e::ABY, 4 },{ "NOP", &e::NOP, &e::IMP, 2 },{ "___", &e::XXX, &e::IMP, 7 },{ "___", &e::NOP, &e::IMP, 4 },{ "CMP", &e::CMP, &e::ABX, 4 },{ "DEC", &e::DEC, &e::ABX, 7 },{ "___", &e::XXX, &e::IMP, 7 },
            { "CPX", &e::CPX, &e::IMM, 2 },{ "SBC", &e::SBC, &e::IZX, 6 },{ "___", &e::NOP, &e::IMP, 2 },{ "___", &e::XXX, &e::IMP, 8 },{ "CPX", &e::CPX, &e::ZPG, 3 },{ "SBC", &e::SBC, &e::ZPG, 3 },{ "INC", &e::INC, &e::ZPG, 5 },{ "___", &e::XXX, &e::IMP, 5 },{ "INX", &e::INX, &e::IMP, 2 },{ "SBC", &e::SBC, &e::IMM, 2 },{ "NOP", &e::NOP, &e::IMP, 2 },{ "___", &e::SBC, &e::IMP, 2 },{ "CPX", &e::CPX, &e::ABS, 4 },{ "SBC", &e::SBC, &e::ABS, 4 },{ "INC", &e::INC, &e::ABS, 6 },{ "___", &e::XXX, &e::IMP, 6 },
            { "BEQ", &e::BEQ, &e::REL, 2 },{ "SBC", &e::SBC, &e::IZY, 5 },{ "___", &e::XXX, &e::IMP, 2 },{ "___", &e::XXX, &e::IMP, 8 },{ "___", &e::NOP, &e::IMP, 4 },{ "SBC", &e::SBC, &e::ZPX, 4 },{ "INC", &e::INC, &e::ZPX, 6 },{ "___", &e::XXX, &e::IMP, 6 },{ "SED", &e::SED, &e::IMP, 2 },{ "SBC", &e::SBC, &e::ABY, 4 },{ "NOP", &e::NOP, &e::IMP, 2 },{ "___", &e::XXX, &e::IMP, 7 },{ "___", &e::NOP, &e::IMP, 4 },{ "SBC", &e::SBC, &e::ABX, 4 },{ "INC", &e::INC, &e::ABX, 7 },{ "___", &e::XXX, &e::IMP, 7 },
        };
}

emu6502::~emu6502()
{

}

void emu6502::cycle()
{
    if (cycles == 0) 
    {
        curr_op = read(pc);
        pc++;

        cycles = instruction_set[curr_op].cycles;

        (this->*instruction_set[curr_op].addr_mode)();
        uint8_t additional_cycle_addr = (this->*instruction_set[curr_op].addr_mode)();
        uint8_t additional_cycle_oper = (this->*instruction_set[curr_op].operation)();
        cycles += (additional_cycle_addr & additional_cycle_oper);
    }
    --cycles;
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

uint8_t emu6502::IMP()
{
    return 0;
}