#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include "ports.h"

#define VIDEO_ADDRESS 0xb8000
#define MAX_ROWS 25
#define MAX_COLS 80
#define WHITE_ON_BLACK 0x0f

uint16_t *video_memory = (uint16_t *)VIDEO_ADDRESS;

uint8_t cursor_x = 0;
uint8_t cursor_y = 0;

void scroll()
{
    for (int row = 1; row < MAX_ROWS; row++)
    {
        for (int col = 0; col < MAX_COLS; col++)
        {
            uint16_t character = video_memory[row * MAX_COLS + col];
            video_memory[(row - 1) * MAX_COLS + col] = character;
        }
    }

    uint16_t blank = WHITE_ON_BLACK << 8 | ' ';
    for (int col = 0; col < MAX_COLS; col++)
    {
        video_memory[(MAX_ROWS - 1) * MAX_COLS + col] = blank;
    }

    cursor_y--;
}

void putcar(unsigned char c)
{
    uint8_t attribute_byte = WHITE_ON_BLACK;

    if (c == '\n')
    {
        cursor_x = 0;
        cursor_y++;
    }
    else if (c == '\b')
    {
        if (cursor_x > 0)
        {
            cursor_x--;
        }
        else if (cursor_y > 0)
        {
            cursor_x = MAX_COLS - 1;
            cursor_y--;
        }
    }
    else
    {
        uint16_t character = attribute_byte << 8 | c;
        video_memory[cursor_y * MAX_COLS + cursor_x] = character;

        cursor_x++;
        if (cursor_x >= MAX_COLS)
        {
            cursor_x = 0;
            cursor_y++;
        }

        if (cursor_y >= MAX_ROWS)
        {
            scroll();
        }
    }
}

int strlen(char *s)
{
    int i = 0;
    while (*s++)
        i++;
    return i;
}

void itoa(char *buf, unsigned long int n, int base)
{
    unsigned long int tmp;
    int i, j;

    tmp = n;
    i = 0;

    do
    {
        tmp = n % base;
        buf[i++] = (tmp < 10) ? (tmp + '0') : (tmp + 'a' - 10);
    } while (n /= base);
    buf[i--] = 0;

    for (j = 0; j < i; j++, i--)
    {
        tmp = buf[j];
        buf[j] = buf[i];
        buf[i] = tmp;
    }
}

void printk(char *s, ...)
{
    va_list ap;

    char buf[16];
    int i, j, size, buflen, neg;

    unsigned char c;
    int ival;
    unsigned int uival;

    va_start(ap, s);

    while ((c = *s++))
    {
        size = 0;
        neg = 0;

        if (c == 0)
            break;
        else if (c == '%')
        {
            c = *s++;
            if (c >= '0' && c <= '9')
            {
                size = c - '0';
                c = *s++;
            }

            if (c == 'd')
            {
                ival = va_arg(ap, int);
                if (ival < 0)
                {
                    uival = 0 - ival;
                    neg++;
                }
                else
                    uival = ival;
                itoa(buf, uival, 10);

                buflen = strlen(buf);
                if (buflen < size)
                    for (i = size, j = buflen; i >= 0;
                         i--, j--)
                        buf[i] =
                            (j >=
                             0)
                                ? buf[j]
                                : '0';

                if (neg)
                    printk("-%s", buf);
                else
                    printk(buf);
            }
            else if (c == 'u')
            {
                uival = va_arg(ap, int);
                itoa(buf, uival, 10);

                buflen = strlen(buf);
                if (buflen < size)
                    for (i = size, j = buflen; i >= 0;
                         i--, j--)
                        buf[i] =
                            (j >=
                             0)
                                ? buf[j]
                                : '0';

                printk(buf);
            }
            else if (c == 'x' || c == 'X')
            {
                uival = va_arg(ap, int);
                itoa(buf, uival, 16);

                buflen = strlen(buf);
                if (buflen < size)
                    for (i = size, j = buflen; i >= 0;
                         i--, j--)
                        buf[i] =
                            (j >=
                             0)
                                ? buf[j]
                                : '0';

                printk("0x%s", buf);
            }
            else if (c == 'p')
            {
                uival = va_arg(ap, int);
                itoa(buf, uival, 16);
                size = 8;

                buflen = strlen(buf);
                if (buflen < size)
                    for (i = size, j = buflen; i >= 0;
                         i--, j--)
                        buf[i] =
                            (j >=
                             0)
                                ? buf[j]
                                : '0';

                printk("0x%s", buf);
            }
            else if (c == 's')
            {
                printk((char *)va_arg(ap, int));
            }
        }
        else
            putcar(c);
    }

    return;
}