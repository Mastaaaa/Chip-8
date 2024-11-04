//
//  Processor.cpp
//  Chip-8
//
//
//
#include "Processor.h"

void Processor::setMemory(int address, uint8_t value){
    if(address >= 0x200 && address < 0x1000){
        memory[address] = value;
    }
    
    if(address < 0x200){
        std::cout << "Writing in innaccesible memory";
    }
}

uint8_t Processor::getMemory(int address) const{
    if(address < 0x1000){
        return memory[address];
    }
    //return 2 = error getting value from memory
    return 2;
};

void Processor::setRegister(int index, uint8_t value){
    if(index < 16){
        V[index] = value;
    }
}

uint8_t Processor::getRegister(int index){
    if(index < 16){
        return V[index];
    }
    //return 3 = error getting value from register
    return 3;
}


void Processor::setRegisterPointer(uint16_t value){
    I = value;
}

uint16_t Processor::getRegisterPointer(){
    return I;
}

void Processor::setProgramCounter(uint16_t value){
    pc = value;
}

uint16_t Processor::getProgramCounter(){
    return pc;
}

void Processor::setStack(int address, uint16_t value){
    if(address < 25) stack[address] = value;
    else std::cout << "stack error, trying to write on full stack";
}

uint16_t Processor::getStack(int address){
    if(address < 25 )
        return stack[address];
    //return 4 = error getting value from stack
    return 4;
}

void Processor::setStackPointer(uint8_t value){
    stackPointer = value;
}

uint8_t Processor::getStackPointer(){
    return stackPointer;
}

void Processor::initialize(){
    //clearing memory
    std::fill(std::begin(memory), std::end(memory), 0);
    //clearing registers
    std::fill(std::begin(V), std::end(V), 0);
    //clearing stack
    std::fill(std::begin(stack), std::end(stack), 0);
    //setting up all pointers
    setProgramCounter(0x200);
    setRegisterPointer(0x0000);
    setStackPointer(0x0000);
}

bool Processor::openRom(const std::string& path){
    std::ifstream romFile(path, std::ios::binary);
    if(!romFile){
        std::cerr << "Error opening rom at path" << path << std::endl;
        return false;
    }
    
    //read data from buffer
    romFile.read(reinterpret_cast<char*>(&memory[0x200]), MEMSIZE - 0x200);
    if(romFile.gcount() == 0){
        std::cerr << "Error, rom is empty or corrupted" << std::endl;
    }
    romFile.close();
    return true;
}
