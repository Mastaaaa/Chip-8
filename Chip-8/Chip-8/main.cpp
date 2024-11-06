//
//  main.cpp
//  Chip-8
//
//
//

#include <iostream>
#include <unistd.h>
#include "Processor.h"

int main(int argc, const char * argv[]) {
    
    //startup routine
    Processor chip_8;
    for(int i = 0; i < MEMSIZE; i++){
        if(static_cast<int>(chip_8.getMemory(i)) != 0){
            std::cout << "Errore initializating memory, aborting...";
            return -1;
        }
    }
    for(int i = 0; i < NUM_REGISTRY; i++)
        if(static_cast<int>(chip_8.getRegistry(i)) != 0){
            std::cout << "Errore initializating registry, aborting...";
            return -1;
        }
    for(int i = 0; i < NUM_REGISTRY; i++)
        if(chip_8.getStack(i) != 0){
            std::cout << "Errore initializating stack, aborting...";
            return -1;
        }
    if(chip_8.getProgramCounter() != 0x200){
        std::cout << "Errore initializating programCounter, aborting...";
        return -1;
    }
    if(chip_8.getRegistryPointer() != 0x0000){
        std::cout << "Errore initializating registryPointer, aborting...";
        return -1;
    }
    if(chip_8.getStackPointer() != 0x0000){
        std::cout << "Errore initializating stackPointer, aborting...";
        return -1;
    }
    //opening rom
    const std::string romPath = "../Rom/2-ibm-logo.ch8";
    chip_8.openRom(romPath);
    chip_8.memoryDump();
    chip_8.emulateCycle();
}
