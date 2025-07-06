/*
 * EEPROM_24cXX_lib.c
 *
 *  Created on: Jul 2, 2025
 *      Authors: Artyom Skibitskiy
 * 		Библиотека для флешек 24-ой серии.
 */

#include "EEPROM_24cXX_lib.h"
uint8_t data_buff[AT24CXX_PAGE_BYTE];

//адрес ячейки куда начнем писать, указатель на массив который запишем, размер этого массива
//вернет адрес последней ячейки или 0 в случае ошибки
uint16_t AT24_Write_Data(uint16_t address, uint8_t *data, uint16_t size)
{
    if ((address + size) <= AT24CXX_MAX_MEM_ADDRESS)
    {
        uint16_t page_count_write = address / AT24CXX_PAGE_BYTE;                                            // узнаем на какой странице мы находимся
        uint16_t byte_count_write = AT24CXX_PAGE_BYTE - (address - (page_count_write * AT24CXX_PAGE_BYTE)); // узнаем сколько байт нужно отправить до следуещей страницы
        if (byte_count_write >= size) // если размер данных помещается в остаток до конца страницы
		{
            memcpy(data_buff, data, size);
            #if defined(AT24C01) || defined(AT24C02)
                I2C_Mem_Write(Address, address, I2C_MEMADD_SIZE_8BIT, (uint8_t *) data_buff, size, 10);
            #else
                I2C_Mem_Write(Address, address, I2C_MEMADD_SIZE_16BIT, (uint8_t *) data_buff, size, 10);
            #endif
            delay(10);
        }
        else // если размер данных не помещается в остаток до конца страницы         
        {
            memcpy(data_buff, data, byte_count_write);
            #if defined(AT24C01) || defined(AT24C02)
                I2C_Mem_Write(Address, address, I2C_MEMADD_SIZE_8BIT, (uint8_t *) data_buff, byte_count_write, 10);
            #else
                I2C_Mem_Write(Address, address, I2C_MEMADD_SIZE_16BIT, (uint8_t *) data_buff, byte_count_write, 10);
            #endif
            delay(10);
            size = size - byte_count_write;
            address = address + byte_count_write;
            uint16_t data_offset = byte_count_write;
            while (size >= AT24CXX_PAGE_BYTE)
            {
                memcpy(data_buff, data + data_offset, AT24CXX_PAGE_BYTE);
                #if defined(AT24C01) || defined(AT24C02)
                    I2C_Mem_Write(Address, address, I2C_MEMADD_SIZE_8BIT, (uint8_t *) data_buff, AT24CXX_PAGE_BYTE, 10);
                #else
                    I2C_Mem_Write(Address, address, I2C_MEMADD_SIZE_16BIT, (uint8_t *) data_buff, AT24CXX_PAGE_BYTE, 10);
                #endif
                delay(10);
                size -= AT24CXX_PAGE_BYTE;
                address += AT24CXX_PAGE_BYTE;
                data_offset += AT24CXX_PAGE_BYTE;
            }
            if (size)
			{
                memcpy(data_buff, data + data_offset, size);
                #if defined(AT24C01) || defined(AT24C02)
                    I2C_Mem_Write(Address, address, I2C_MEMADD_SIZE_8BIT, (uint8_t *) data_buff, size, 10);
                #else
                    I2C_Mem_Write(Address, address, I2C_MEMADD_SIZE_16BIT, (uint8_t *) data_buff, size, 10);
                #endif
                delay(10);
			}

        }
        // delay(10);
        return address + size;
    }
    else // если размер данных не помещается в память
    {
        return 0;
    }
}

//адрес ячейки откуда начнем считывать, указатель на массив куда считываем, размер этого массива
//вернет адрес последней ячейки или 0 в случае ошибки
uint16_t AT24_Read_Data(uint16_t address, uint8_t *data, uint16_t size)
{
	if ((address + size) <= AT24CXX_MAX_MEM_ADDRESS)
	{

    #if defined(AT24C01) || defined(AT24C02)
        I2C_Mem_Read(Address, address, I2C_MEMADD_SIZE_8BIT,(uint8_t *) data, size, 10);
    #else
        I2C_Mem_Read(Address, address, I2C_MEMADD_SIZE_16BIT, (uint8_t *) data, size, 10);
    #endif

		return address + size;
	}
	else
	{
		return 0;
	}
}
