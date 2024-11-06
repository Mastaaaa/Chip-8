//
//  Processor.h
//  Chip-8
//
//
//
#pragma once
#define MEMSIZE 4096
#define NUM_REGISTRY 16
#define STACK_SIZE 25
#include <cstdint>
#include <iostream>
#include <fstream>

class Processor{
    
private:
    //Array representing system memory
    uint8_t memory[MEMSIZE];
    //array of 16 registers from V0 to VF. Note that VF could be used for flag purpose
    uint8_t registry[NUM_REGISTRY];
    //pointer register ??? read more.
    uint16_t registryPointer;
    //program counter
    uint16_t pc;
    //instruction stack, size to define
    uint16_t stack[STACK_SIZE];
    //stack pointer
    uint8_t stackPointer;
    
public:
    Processor();
    void initialize();
    void memoryDump() const;
    void emulateCycle();
    void clearScreen();
    
    /* getter and setter
    /
    /
    */
    void setMemory(int address, uint8_t value);
    uint8_t getMemory(int index) const;
    
    void setRegistry(int address, uint8_t value);
    uint8_t getRegistry(int index) const;
    
    void setRegistryPointer(uint16_t value);
    uint16_t getRegistryPointer() const;
    
    void setProgramCounter(uint16_t value);
    uint16_t getProgramCounter() const;
    
    void setStack(int address, uint16_t value);
    uint16_t getStack(int address) const;
    
    void setStackPointer(uint8_t value);
    uint8_t getStackPointer() const;
    
    /* ROM handling functions
    /
    /
    */
    bool openRom(const std::string& path);
};
