#include <Windows.h>
#include <iostream>


int i = 200;
int main()
{
	while (true)
	{
		printf("value of i \t= %d \r\n", i);
		printf("address of i \t= 0x%p \r\n", &i);
		Sleep(2000);
	}

	system("pause");
	return 0;
}