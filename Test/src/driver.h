#pragma once
#include <Windows.h>
#include <winioctl.h>

typedef struct _IOBUFFER
{
	ULONGLONG Destination;
	ULONGLONG Source;
	ULONGLONG Length;
	ULONG     DestinationPid;
	ULONG     SourcePid;
} IOBUFFER, *PIOBUFFER;

#define IOCTL_IO_READ		CTL_CODE(FILE_DEVICE_UNKNOWN, 0x800, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_IO_WRITE		CTL_CODE(FILE_DEVICE_UNKNOWN, 0x801, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_IO_PID		CTL_CODE(FILE_DEVICE_UNKNOWN, 0x802, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_IO_MOUDLE		CTL_CODE(FILE_DEVICE_UNKNOWN, 0x803, METHOD_BUFFERED, FILE_ANY_ACCESS)

class driver
{
public:
	driver();
	~driver();

	ULONGLONG GetGameModule();
	DWORD GetGamePid();

	template <typename T> inline T RPM(DWORD_PTR Addr);
	template <typename T> inline T RPM(DWORD_PTR Addr, SIZE_T Size);
	template <typename T> inline bool RPM(DWORD_PTR Addr, T OuterBuffer, SIZE_T Size);
	template <typename T> inline bool WPM(DWORD_PTR Addr, T value);
	template <typename T> inline bool WPM(DWORD_PTR Addr, T value, SIZE_T Size);

protected:
	HANDLE hDriver;
};

template<typename T>
inline T driver::RPM(DWORD_PTR Addr)
{
	T readBuffer = NULL;

	DWORD Bytes;
	_IOBUFFER ReadRequest
	{
		(ULONGLONG)&readBuffer,
		(ULONGLONG)Addr,
		sizeof(T),
		(ULONG)GetCurrentProcessId(),
		0
	};
	DeviceIoControl(
		hDriver,
		IOCTL_IO_READ,
		&ReadRequest,
		sizeof(ReadRequest),
		&ReadRequest,
		sizeof(ReadRequest),
		&Bytes,
		NULL);
	return (T)readBuffer;
}


template<typename T>
inline T driver::RPM(DWORD_PTR Addr, SIZE_T Size)
{
	T readBuffer = {};

	DWORD Bytes;
	_IOBUFFER ReadRequest
	{
		(ULONGLONG)&readBuffer,
		(ULONGLONG)Addr,
		Size,
		(ULONG)GetCurrentProcessId(),
		0
	};
	DeviceIoControl(
		hDriver,
		IOCTL_IO_READ,
		&ReadRequest,
		sizeof(ReadRequest),
		&ReadRequest,
		sizeof(ReadRequest),
		&Bytes,
		NULL);
	return (T)readBuffer;
}

template<typename T>
inline bool driver::RPM(DWORD_PTR Addr, T OuterBuffer, SIZE_T Size)
{
	DWORD Bytes;
	_IOBUFFER ReadRequest
	{
		(ULONGLONG)OuterBuffer,
		(ULONGLONG)Addr,
		Size,
		(ULONG)GetCurrentProcessId(),
		0
	};
	return DeviceIoControl(
		hDriver,
		IOCTL_IO_READ,
		&ReadRequest,
		sizeof(ReadRequest),
		&ReadRequest,
		sizeof(ReadRequest),
		&Bytes,
		NULL);
}

template<typename T>
inline bool driver::WPM(DWORD_PTR Addr, T value)
{
	T writeBuffer = value;
	DWORD Bytes;
	_IOBUFFER  WriteRequest
	{
		(ULONGLONG)&writeBuffer,
		(ULONGLONG)Addr,
		sizeof(T),
		(ULONG)GetCurrentProcessId(),
		0
	};
	return DeviceIoControl(
		hDriver,
		IOCTL_IO_WRITE,
		&WriteRequest,
		sizeof(WriteRequest),
		&WriteRequest,
		sizeof(WriteRequest),
		&Bytes,
		NULL);
}

template<typename T>
inline bool driver::WPM(DWORD_PTR Addr, T value, SIZE_T Size)
{
	DWORD Bytes;
	_IOBUFFER  WriteRequest
	{
		(ULONGLONG)value,
		(ULONGLONG)Addr,
		Size,
		(ULONG)GetCurrentProcessId(),
		0
	};

	return DeviceIoControl(
		hDriver,
		IOCTL_IO_WRITE,
		&WriteRequest,
		sizeof(WriteRequest),
		&WriteRequest,
		sizeof(WriteRequest),
		&Bytes,
		NULL);
}

extern driver drv;