#include <stdint.h>
#include "fat.h"
#include "memory.h"
#include "stdio.h"
#include "gdt.h"

#define KERNEL_SECTORS 16
#define KERNEL_FIRST_SECTOR 20

void load_kernel() {
    uint32_t lba_addr = KERNEL_FIRST_SECTOR;
    uint8_t buffer[KERNEL_SECTORS * SECTOR_SIZE];
    
    // Charge les secteurs du disque contenant le kernel
    if (read_disk(lba_addr, KERNEL_SECTORS, buffer) != 0) {
        // Gestion d'erreur
        return;
    }
    
    // Copie les données du kernel en mémoire à l'adresse 0x10000
    uint8_t* kernel_addr = (uint8_t*)0x10000;
    memcpy(kernel_addr, buffer, KERNEL_SECTORS * SECTOR_SIZE);
}

void stage2_entry()
{
    init_gdt();
    memory_init();

    load_kernel();
    asm volatile("jmp 0x10000");
}