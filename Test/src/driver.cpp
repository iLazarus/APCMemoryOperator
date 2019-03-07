#include "driver.h"

driver::driver()
{
	hDriver = CreateFileA("\\\\.\\KingSoft", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, 0, OPEN_EXISTING, 0, 0);
	if (hDriver == INVALID_HANDLE_VALUE)
	{
		MessageBox(NULL, "驱动未安装", "警告", MB_OK);
	}
}

driver::~driver()
{
	if (hDriver != INVALID_HANDLE_VALUE)
	{
		CloseHandle(hDriver);
	}
}

ULONGLONG driver::GetGameModule()
{
	if (hDriver == INVALID_HANDLE_VALUE) return 0;
	ULONGLONG readBuffer;
	DWORD Bytes;
	_IOBUFFER ReadRequest
	{
		(ULONGLONG)&readBuffer,
		(ULONGLONG)0x0,
		sizeof(ULONGLONG),
		(ULONG)GetCurrentProcessId(),
		0
	};
	BOOL stat = DeviceIoControl(
		hDriver,
		IOCTL_IO_MOUDLE,
		&ReadRequest,
		sizeof(ReadRequest),
		&ReadRequest,
		sizeof(ReadRequest),
		&Bytes,
		NULL);
	return stat ? readBuffer : 0;
}

DWORD driver::GetGamePid()
{
	if (hDriver == INVALID_HANDLE_VALUE) return 0;
	DWORD readBuffer;
	DWORD Bytes;
	_IOBUFFER ReadRequest
	{
		(ULONGLONG)&readBuffer,
		(ULONGLONG)0x0,
		sizeof(ULONGLONG),
		(ULONG)GetCurrentProcessId(),
		0
	};
	BOOL stat = DeviceIoControl(
		hDriver,
		IOCTL_IO_PID,
		&ReadRequest,
		sizeof(ReadRequest),
		&ReadRequest,
		sizeof(ReadRequest),
		&Bytes,
		NULL);
	return stat ? readBuffer : 0;
}

driver drv;