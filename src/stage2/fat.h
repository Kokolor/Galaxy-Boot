#ifndef FAT_H
#define FAT_H

#include <stdint.h>
#include "ports.h"

#define SECTOR_SIZE 512

int disk_read(unsigned int lba_addr, unsigned char *buffer, unsigned int num_sectors);

#endif
