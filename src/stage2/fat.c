#include <stdint.h>
#include "memory.h"
#include "fat.h"
#include "ports.h"
#include "stdio.h"

int disk_read(unsigned int lba_addr, unsigned char *buffer, unsigned int num_sectors)
{
    unsigned int sector;
    outb(0x1F2, num_sectors);                              // number of sectors to read
    outb(0x1F3, (unsigned char)lba_addr);                  // low 8 bits of LBA
    outb(0x1F4, (unsigned char)(lba_addr >> 8));           // next 8 bits of LBA
    outb(0x1F5, (unsigned char)(lba_addr >> 16));          // next 8 bits of LBA
    outb(0x1F6, (unsigned char)((lba_addr >> 24) | 0xE0)); // highest 8 bits of LBA + 0xE0
    outb(0x1F7, 0x20);                                     // command to read sectors

    // wait for disk to be ready
    while ((inb(0x1F7) & 0x80) != 0)
        ;

    // read sector data
    for (sector = 0; sector < num_sectors; ++sector)
    {
        int i;
        for (i = 0; i < SECTOR_SIZE; ++i)
        {
            buffer[i] = inb(0x1F0);
        }
        buffer += SECTOR_SIZE;
    }

    return 0;
}
