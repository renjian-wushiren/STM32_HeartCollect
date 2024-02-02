#ifndef __DEBUG_H__
#define __DEBUG_H__
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include "Dri_USART1.h"

// #define DEBUG
#ifdef DEBUG
#define debug_init() Debug_Init()
#define FILENAME (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)
#define debug_printf(format, ...) printf("[%s:%d]--" format, FILENAME, __LINE__, ##__VA_ARGS__)
#define debug_printfln(format, ...) printf("[%s:%d]--" format "\r\n", __FILE__, __LINE__, ##__VA_ARGS__)

#else
#define debug_init()
#define debug_printf(format, ...)
#define debug_printfln(format, ...)
#endif // DEBUG
void Debug_Init(void);
#endif