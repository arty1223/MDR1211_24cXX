/*
 * EEPROM_24cXX_lib.c
 *
 *  Created on: Jul 2, 2025
 *      Authors: Artyom Skibitskiy
 * 		Библиотека для флешек 24-ой серии.
 */

#pragma once
#include "app.h"
#include <stdio.h>
#include <string.h>


#define Address 0x50 << 1 // адрес устройства

#ifndef EEPROM_24cXX_LIB_H_
#define EEPROM_24cXX_LIB_H_

//#define AT24C01
//#define AT24C02
//#define AT24C04
//#define AT24C08
//#define AT24C16
//#define AT24C32
#define AT24C64
// #define AT24C128
//#define AT24C256
//#define AT24C512

/*----------------------------Макросы для разных микросхем памяти--------------------------------------*/
#if defined(AT24C01)
    #define AT24CXX_PAGE_BYTE               8
    #define AT24CXX_MAX_MEM_ADDRESS         128
#elif defined(AT24C02)
    #define AT24CXX_PAGE_BYTE               8
    #define AT24CXX_MAX_MEM_ADDRESS         256
#elif defined(AT24C04)
    #define AT24CXX_PAGE_BYTE               16
    #define AT24CXX_MAX_MEM_ADDRESS         512
#elif defined(AT24C08)
    #define AT24CXX_PAGE_BYTE               16
    #define AT24CXX_MAX_MEM_ADDRESS         1024
#elif defined(AT24C16)
    #define AT24CXX_PAGE_BYTE               16
    #define AT24CXX_MAX_MEM_ADDRESS         2048
#elif defined(AT24C32)
    #define AT24CXX_PAGE_BYTE               32
    #define AT24CXX_MAX_MEM_ADDRESS         4096
#elif defined(AT24C64)
    #define AT24CXX_PAGE_BYTE               32
    #define AT24CXX_MAX_MEM_ADDRESS         8192
#elif defined(AT24C128)
#define AT24CXX_PAGE_BYTE               64
#define AT24CXX_MAX_MEM_ADDRESS         16384
#elif defined(AT24C256)
    #define AT24CXX_PAGE_BYTE               64
    #define AT24CXX_MAX_MEM_ADDRESS         32768
#elif defined(AT24C512)
    #define AT24CXX_PAGE_BYTE               128
    #define AT24CXX_MAX_MEM_ADDRESS         65536
#endif
/*----------------------------Макросы для разных микросхем памяти--------------------------------------*/

uint16_t AT24_Write_Data(uint16_t address, uint8_t *data, uint16_t size);
uint16_t AT24_Read_Data(uint16_t address, uint8_t *data, uint16_t size);

#endif /* EEPROM_24cXX_LIB_H_ */
