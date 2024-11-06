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

void Processor::setRegistry(int index, uint8_t value){
    if(index < 16){
        registry[index] = value;
    }
}

uint8_t Processor::getRegistry(int index) const{
    if(index < 16){
        return registry[index];
    }
    //return 3 = error getting value from register
    return 3;
}


void Processor::setRegistryPointer(uint16_t value){
    registryPointer = value;
}

uint16_t Processor::getRegistryPointer() const{
    return registryPointer;
}

void Processor::setProgramCounter(uint16_t value){
    pc = value;
}

uint16_t Processor::getProgramCounter() const{
    return pc;
}

void Processor::setStack(int address, uint16_t value){
    if(address < 25) stack[address] = value;
    else std::cout << "stack error, trying to write on full stack";
}

uint16_t Processor::getStack(int address) const{
    if(address < 25 )
        return stack[address];
    //return 4 = error getting value from stack
    return 4;
}

void Processor::setStackPointer(uint8_t value){
    stackPointer = value;
}

uint8_t Processor::getStackPointer() const{
    return stackPointer;
}

Processor::Processor(){
    initialize();
}

void Processor::initialize(){
    //clearing memory
    std::fill(std::begin(memory), std::end(memory), 0);
    //clearing registers
    std::fill(std::begin(registry), std::end(registry), 0);
    //clearing stack
    std::fill(std::begin(stack), std::end(stack), 0);
    //setting up all pointers
    setProgramCounter(0x200);
    setRegistryPointer(0x0000);
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
        return false;
    }
    romFile.close();
    return true;
}

void Processor::memoryDump() const{
    for(int i = 0x200; i < MEMSIZE; i++){
        std::cout << "Byte " << i << ": " << std::hex << static_cast<int>(Processor::getMemory(i)) << std::endl;
    }
}

void Processor::emulateCycle(){
    //fetch
    uint16_t instruction = (memory[pc] << 8) | memory[pc + 1];
    uint16_t address = 0x0000; //NNN
    uint8_t value = 0x00; //NN
    uint8_t registryX = 0x00; //X
    uint8_t registryY = 0x00; //Y
    //decode
    switch (instruction & 0xF000) {
        //starting with 0 OPCODE
        case 0x0000:
            if(instruction == 0x00E0){
                //OPCODE 00E0
                clearScreen();
                break;
            }
            if(instruction == 0x00EE){
                //OPCODE 00EE
                //return from subroutine;
                //----------TODO------------
                break;
            }
            address = instruction & 0x0FFF;
            //esegui subroutine a NNN;
            //--------TODO----------------
            break;
        //starting with 1 OPCODE
        case 0x1000:
            //OPCODE 1NNN
            address = instruction & 0x0FFF;
            pc = address;
            break;
        case 0x2000:
            //OPCODE 2NNN
            address = instruction & 0x0FFF;
            stack[stackPointer++] = pc;
            pc = address;
            break;
        case 0x3000:
            //OPCODE 3XNN
            registryX = instruction & 0x0F00;
            value = instruction & 0x00FF;
            if(registryX == value)
                pc++;
            break;
        case 0x4000:
            //OPCODE 4XNN
            registryX = instruction & 0x0F00;
            value = instruction & 0x00FF;
            if(registryX != value)
                pc++;
            break;
        case 0x5000:
            //OPCODE 5XNN
            registryX = instruction & 0x0F00;
            registryY = instruction & 0x00F0;
            if(registryX == registryY)
                pc++;
            break;
        case 0x6000:
            registryX = instruction & 0x0F00;
            value = instruction & 0x00FF;
            setRegistry(registryX, value);
            break;
        case 0x7000:
            registryX = instruction & 0x0F00;
            value = instruction & 0x00FF;
            setRegistry(registryX, value + registry[registryX]);
        case 0x8000:
            registryX = instruction & 0x0F00;
            registryY = instruction & 0x00F0;
            switch (instruction & 0x000F) {
                case 0x0000:
                    setRegistry(registryX, registry[registryY]);
                    break;
                case 0x0001:
                    setRegistry(registryX,  registry[registryX] | registry[registryY]);
                    break;
                case 0x0002:
                    setRegistry(registryX,  registry[registryX] & registry[registryY]);
                    break;
                case 0x0003:
                    setRegistry(registryX,  registry[registryX] ^ registry[registryY]);
                    break;
                case 0x0004:{
                    uint16_t sum = registry[registryX] + registry[registryY];
                    setRegistry(registryX,  sum & 0xFF);
                    registry[0xF] = (sum > 0x00FF) ? 1 : 0;
                    break;
                }
                case 0x0005:{
                    int16_t subtraction = static_cast<int16_t>(registry[registryX]) - static_cast<int16_t>(registry[registryY]);
                    registry[0xF] = (registry[registryY] > registry[registryX]) ? 1 : 0;
                    setRegistry(registryX,  static_cast<uint8_t>(subtraction));
                    break;
                }
                case 0x0006:{
                    uint8_t tempY = registry[registryY];
                    setRegistry(0xF, registry[registryY] & 0x01);
                    setRegistry(registryX, tempY >> 1);
                    break;
                }
                default:
                    std::cout << "Error in instruction 8XXX: no matching instruction";
                    break;
            }
        default:
            
            break;
    }
    
}
