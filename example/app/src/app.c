#include "app.h"

int main(void)
{
	RST_CLK_DeInit();
	CLK_Init_80_mhz();
	initSystick();
	initI2C();

	uint8_t data = 45;
	uint8_t buffer[AT24CXX_MAX_MEM_ADDRESS] = {
		0,
	};
	// создаем буффер для работы с флешкой размером с ее.
	// у К1986ВЕ92FI 32Кб оперативной памяти, объём флешки в моем случае 24c64 - 8Кб что нормально помещается.
	// конечно, забивать оперативку буффером не лучшая идея, но для демонстрации - пойдет.
	for (uint16_t i = 0; i < AT24CXX_MAX_MEM_ADDRESS; i++)
		buffer[i] = i; // забьём буффер числами

	AT24_Write_Data(0, &data, sizeof(data)); // запишем data в ячейку 0
	data = 0; // очистим data
	AT24_Read_Data(0, &data, sizeof(data));// считаем данные ячейки 0 в байт data

	AT24_Write_Data(0, buffer, sizeof(buffer)); // заполним флешку данными из буффера
	memset(buffer,0,sizeof(buffer)); // забьем буффер нулями
	AT24_Read_Data(0, buffer, sizeof(buffer)); // а затем считаем все с флешки в него.

	while (1)
	{
	}
}
