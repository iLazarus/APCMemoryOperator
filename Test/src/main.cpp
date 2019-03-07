#include "driver.h"
#include <iostream>

int main()
{
	printf("try read \r\n");
	printf("TslGame.exe module base  = 0x%I64X \r\n", drv.GetGameModule());
	printf("TslGame.exe value of variable i = %d \r\n", drv.RPM<int>(drv.GetGameModule() + 0x3034));
	printf("TslGame.exe value of variable i = %d \r\n", drv.RPM<int>(drv.GetGameModule() + 0x3034, sizeof(int)));
	int j = 5;
	drv.RPM(drv.GetGameModule() + 0x3034, &j, sizeof(int));
	printf("TslGame.exe value of variable i = %d \r\n", j);

	drv.WPM<int>(drv.GetGameModule() + 0x3034, 500);
	printf("TslGame.exe value of variable i = %d \r\n", drv.RPM<int>(drv.GetGameModule() + 0x3034));

	byte k = 0xF;
	drv.WPM(drv.GetGameModule() + 0x3034, &k, sizeof(byte));
	printf("TslGame.exe value of variable i = %d \r\n", drv.RPM<int>(drv.GetGameModule() + 0x3034));



	system("pause");

}