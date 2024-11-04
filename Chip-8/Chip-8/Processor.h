//
//  Emulator.h
//  Chip-8
//
//
//
#define MEMSIZE 4096

#include <cstdint>
#include <iostream>
#include <fstream>

class Processor{
    
private:
    //Array representing system memory
    uint8_t memory[MEMSIZE];
    //array of 16 registers from V0 to VF. Note that VF could be used for flag purpose
    uint8_t V[16];
    //pointer register ??? read more.
    uint16_t I;
    //program counter
    uint16_t pc;
    //instruction stack, size to define
    uint16_t stack[25];
    //stack pointer
    uint8_t stackPointer;
    
public:
    void initialize();
    /* getter and setter
    /
    /
    */
    void setMemory(int address, uint8_t value);
    uint8_t getMemory(int index) const;
    
    void setRegister(int address, uint8_t value);
    uint8_t getRegister(int index);
    
    void setRegisterPointer(uint16_t value);
    uint16_t getRegisterPointer();
    
    void setProgramCounter(uint16_t value);
    uint16_t getProgramCounter();
    
    void setStack(int address, uint16_t value);
    uint16_t getStack(int address);
    
    void setStackPointer(uint8_t value);
    uint8_t getStackPointer();
    
    /* ROM handling functions
    /
    /
    */
    bool openRom(const std::string& path);
    
    
    
};
