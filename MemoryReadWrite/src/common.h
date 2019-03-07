#pragma once
#include <ntdef.h>
#include <ntifs.h>

NTKERNELAPI PVOID PsGetProcessSectionBaseAddress(__in PEPROCESS Process);
NTKERNELAPI UCHAR * PsGetProcessImageFileName(__in PEPROCESS Process);

typedef struct _IOBUFFER
{
	ULONGLONG Destination;
	ULONGLONG Source;
	ULONGLONG Length;
	ULONG     DestinationPid;
	ULONG     SourcePid;
} IOBUFFER, *PIOBUFFER;

#define TARGET_IMAGENAME	L"\\TslGame\\Binaries\\Win64\\TslGame.exe"
#define TARGET_PROCESSNAME	"TslGame.exe"
#define DEVICE_NAME			L"\\Device\\KingSoft"
#define LINK_NAME			L"\\DosDevices\\KingSoft"
#define LINK_GLOBAL_NAME	L"\\DosDevices\\Global\\KingSoft"

#define IOCTL_IO_READ		CTL_CODE(FILE_DEVICE_UNKNOWN, 0x800, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_IO_WRITE		CTL_CODE(FILE_DEVICE_UNKNOWN, 0x801, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_IO_PID		CTL_CODE(FILE_DEVICE_UNKNOWN, 0x802, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_IO_MOUDLE		CTL_CODE(FILE_DEVICE_UNKNOWN, 0x803, METHOD_BUFFERED, FILE_ANY_ACCESS)


LONGLONG lMoudleBase;
HANDLE hPid;
PVOID DriverBuffer;