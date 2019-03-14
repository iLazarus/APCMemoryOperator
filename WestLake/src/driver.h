#pragma once
#ifndef DRIVER_H
#define DRIVER_H

#include <Windows.h>
#include <winioctl.h>


// driver function and ctl_code define
#define IO_READ_REQUEST CTL_CODE(FILE_DEVICE_UNKNOWN, 0x800 , METHOD_BUFFERED, FILE_SPECIAL_ACCESS) //read
#define IO_WRITE_REQUEST CTL_CODE(FILE_DEVICE_UNKNOWN, 0x801 , METHOD_BUFFERED, FILE_SPECIAL_ACCESS) //write
#define IO_GET_PID_REQUEST CTL_CODE(FILE_DEVICE_UNKNOWN, 0x802 , METHOD_BUFFERED, FILE_SPECIAL_ACCESS) //getPid
#define IO_GET_MODULE_REQUEST CTL_CODE(FILE_DEVICE_UNKNOWN, 0x803 , METHOD_BUFFERED, FILE_SPECIAL_ACCESS) //getModule

//driver r/w struct
typedef struct _IOBUFFER
{
	ULONGLONG UserBufferAdress;
	ULONGLONG GameAddressOffset;
	ULONGLONG Size;
	ULONG     UserPID;
	ULONG     GamePID;
} IOBUFFER, *PIOBUFFER;

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
		IO_READ_REQUEST,
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
		IO_READ_REQUEST,
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
		IO_READ_REQUEST,
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
		IO_WRITE_REQUEST,
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
		IO_WRITE_REQUEST,
		&WriteRequest,
		sizeof(WriteRequest),
		&WriteRequest,
		sizeof(WriteRequest),
		&Bytes,
		NULL); 
}

#endif