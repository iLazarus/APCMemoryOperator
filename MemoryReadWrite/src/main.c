#include "common.h"

VOID NotifyImageLoadCallback(PUNICODE_STRING FullImageName, HANDLE ProcessId, PIMAGE_INFO ImageInfo)
{
	UNREFERENCED_PARAMETER(ImageInfo);
	if (wcsstr(FullImageName->Buffer, TARGET_IMAGENAME))
	{
		NTSTATUS status = STATUS_SUCCESS;
		PEPROCESS targetProcess;
		status = PsLookupProcessByProcessId(ProcessId, &targetProcess);
		if (status != STATUS_SUCCESS || !targetProcess) return;
		__try
		{
			KeAttachProcess((PKPROCESS)targetProcess);
			if (!strcmp((PCHAR)PsGetProcessImageFileName(targetProcess), TARGET_PROCESSNAME))
			{
				hPid = ProcessId;
				lMoudleBase = (DWORD64)PsGetProcessSectionBaseAddress(targetProcess);
				dImageSize = ImageInfo->ImageSize;
			}
			KeDetachProcess();
		}
		__except (GetExceptionCode())
		{
		}
	}
}


VOID DriverUnload(PDRIVER_OBJECT pObj)
{
	PsRemoveLoadImageNotifyRoutine(NotifyImageLoadCallback);
	UNICODE_STRING usLink;
	RtlInitUnicodeString(&usLink, LINK_NAME);
	IoDeleteSymbolicLink(&usLink);
	IoDeleteDevice(pObj->DeviceObject);
}


NTSTATUS DispatchCreate(PDEVICE_OBJECT pObj, PIRP pIrp)
{
	UNREFERENCED_PARAMETER(pObj);
	pIrp->IoStatus.Status = STATUS_SUCCESS;
	pIrp->IoStatus.Information = 0;
	IoCompleteRequest(pIrp, IO_NO_INCREMENT);
	return STATUS_SUCCESS;
}


NTSTATUS DispatchClose(PDEVICE_OBJECT pObj, PIRP pIrp)
{
	UNREFERENCED_PARAMETER(pObj);
	pIrp->IoStatus.Status = STATUS_SUCCESS;
	pIrp->IoStatus.Information = 0;
	IoCompleteRequest(pIrp, IO_NO_INCREMENT);
	return STATUS_SUCCESS;
}

NTSTATUS DispatchIOCTL(PDEVICE_OBJECT pObj, PIRP pIrp)
{
	UNREFERENCED_PARAMETER(pObj);
	NTSTATUS status = STATUS_INVALID_DEVICE_REQUEST;
	PIO_STACK_LOCATION pIrpStack;
	ULONG uIoControlCode;
	PVOID pIoBuffer;
	ULONG uInSize;
	ULONG uOutSize;
	pIrpStack = IoGetCurrentIrpStackLocation(pIrp);
	uIoControlCode = pIrpStack->Parameters.DeviceIoControl.IoControlCode;
	pIoBuffer = pIrp->AssociatedIrp.SystemBuffer;
	uInSize = pIrpStack->Parameters.DeviceIoControl.InputBufferLength;
	uOutSize = pIrpStack->Parameters.DeviceIoControl.OutputBufferLength;

	PIOBUFFER buffer = pIoBuffer;
	DriverBuffer = ExAllocatePoolWithTag(NonPagedPool, buffer->Length, 'Sys');

	switch (uIoControlCode)
	{
	case IOCTL_IO_READ:
	{
		PEPROCESS hClient, hGame;
		KAPC_STATE apc_state;

		if (lMoudleBase == 0 || hPid == 0) break;

		PsLookupProcessByProcessId(hPid, &hGame);
		PsLookupProcessByProcessId((HANDLE)buffer->DestinationPid, &hClient);

		if (DriverBuffer == NULL) break;
		__try
		{
			KeStackAttachProcess(hGame, &apc_state);
			ProbeForRead((CONST PVOID)buffer->Source, buffer->Length, sizeof(CHAR));
			RtlCopyMemory(DriverBuffer, (PVOID)buffer->Source, buffer->Length);
			KeUnstackDetachProcess(&apc_state);
		}
		__except (EXCEPTION_EXECUTE_HANDLER)
		{
			KeUnstackDetachProcess(&apc_state);
			break;
		}
		__try
		{
			KeStackAttachProcess(hClient, &apc_state);
			ProbeForRead((CONST PVOID)buffer->Destination, buffer->Length, sizeof(CHAR));
			RtlCopyMemory((PVOID)buffer->Destination, DriverBuffer, buffer->Length);
			KeUnstackDetachProcess(&apc_state);
		}
		__except (EXCEPTION_EXECUTE_HANDLER)
		{
			KeUnstackDetachProcess(&apc_state);
			break;
		}
		status = STATUS_SUCCESS;
		break;
	}
	case IOCTL_IO_WRITE:
	{
		PEPROCESS hClient, hGame;
		KAPC_STATE apc_state;

		if (lMoudleBase == 0 || hPid == 0) break;

		PsLookupProcessByProcessId(hPid, &hGame);
		PsLookupProcessByProcessId((HANDLE)buffer->DestinationPid, &hClient);

		if (DriverBuffer == NULL) break;
		__try
		{
			KeStackAttachProcess(hClient, &apc_state);
			ProbeForRead((CONST PVOID)buffer->Destination, buffer->Length, sizeof(CHAR));
			RtlCopyMemory(DriverBuffer, (PVOID)buffer->Destination, buffer->Length);
			KeUnstackDetachProcess(&apc_state);
		}
		__except (EXCEPTION_EXECUTE_HANDLER)
		{
			KeUnstackDetachProcess(&apc_state);
			break;
		}
		__try
		{
			KeStackAttachProcess(hGame, &apc_state);
			ProbeForRead((CONST PVOID)buffer->Source, buffer->Length, sizeof(CHAR));
			RtlCopyMemory((PVOID)buffer->Source, DriverBuffer, buffer->Length);
			KeUnstackDetachProcess(&apc_state);
		}
		__except (EXCEPTION_EXECUTE_HANDLER)
		{
			KeUnstackDetachProcess(&apc_state);
			break;
		}

		status = STATUS_SUCCESS;
		break;
	}
	case IOCTL_IO_PID:
	{
		PEPROCESS hClient, hGame;
		KAPC_STATE apc_state;

		if (lMoudleBase == 0 || hPid == 0) break;

		PsLookupProcessByProcessId(hPid, &hGame);
		PsLookupProcessByProcessId((HANDLE)buffer->DestinationPid, &hClient);

		if (DriverBuffer == NULL) break;

		__try
		{
			KeStackAttachProcess(hClient, &apc_state);
			ProbeForRead((CONST PVOID)buffer->Destination, buffer->Length, sizeof(CHAR));
			RtlCopyMemory((PVOID)buffer->Destination, &hPid, buffer->Length);
			KeUnstackDetachProcess(&apc_state);
		}
		__except (EXCEPTION_EXECUTE_HANDLER)
		{
			KeUnstackDetachProcess(&apc_state);
			break;
		}

		status = STATUS_SUCCESS;
		break;
	}
	case IOCTL_IO_MOUDLE:
	{
		PEPROCESS hClient, hGame;
		KAPC_STATE apc_state;

		if (lMoudleBase == 0 || hPid == 0) break;

		PsLookupProcessByProcessId(hPid, &hGame);
		PsLookupProcessByProcessId((HANDLE)buffer->DestinationPid, &hClient);

		if (DriverBuffer == NULL) break;

		__try
		{
			KeStackAttachProcess(hClient, &apc_state);
			ProbeForRead((CONST PVOID)buffer->Destination, buffer->Length, sizeof(CHAR));
			RtlCopyMemory((PVOID)buffer->Destination, &lMoudleBase, buffer->Length);
			KeUnstackDetachProcess(&apc_state);
		}
		__except (EXCEPTION_EXECUTE_HANDLER)
		{
			KeUnstackDetachProcess(&apc_state);
			break;
		}

		status = STATUS_SUCCESS;
		break;
	}

	case IOCTL_IO_IMAGESIZE:
	{
		PEPROCESS hClient, hGame;
		KAPC_STATE apc_state;

		if (lMoudleBase == 0 || hPid == 0) break;

		PsLookupProcessByProcessId(hPid, &hGame);
		PsLookupProcessByProcessId((HANDLE)buffer->DestinationPid, &hClient);

		if (DriverBuffer == NULL) break;

		__try
		{
			KeStackAttachProcess(hClient, &apc_state);
			ProbeForRead((CONST PVOID)buffer->Destination, buffer->Length, sizeof(CHAR));
			RtlCopyMemory((PVOID)buffer->Destination, &dImageSize, buffer->Length);
			KeUnstackDetachProcess(&apc_state);
		}
		__except (EXCEPTION_EXECUTE_HANDLER)
		{
			KeUnstackDetachProcess(&apc_state);
			break;
		}

		status = STATUS_SUCCESS;
		break;
	}
	}
	ExFreePool(DriverBuffer);
	if (status == STATUS_SUCCESS)
		pIrp->IoStatus.Information = uOutSize;
	else
		pIrp->IoStatus.Information = 0;
	pIrp->IoStatus.Status = status;
	IoCompleteRequest(pIrp, IO_NO_INCREMENT);
	return status;
}

NTSTATUS DriverEntry(PDRIVER_OBJECT pObj, PUNICODE_STRING pRegistryString)
{
	UNREFERENCED_PARAMETER(pRegistryString);
	NTSTATUS status = STATUS_SUCCESS;
	UNICODE_STRING ustrLinkName;
	UNICODE_STRING ustrDevName;
	PDEVICE_OBJECT pDevObj;
	pObj->MajorFunction[IRP_MJ_CREATE] = DispatchCreate;
	pObj->MajorFunction[IRP_MJ_CLOSE] = DispatchClose;
	pObj->MajorFunction[IRP_MJ_DEVICE_CONTROL] = DispatchIOCTL;
	pObj->DriverUnload = DriverUnload;
	RtlInitUnicodeString(&ustrDevName, DEVICE_NAME);
	status = IoCreateDevice(pObj, 0, &ustrDevName, FILE_DEVICE_UNKNOWN, 0, FALSE, &pDevObj);
	if (!NT_SUCCESS(status))
		return status;
	if (IoIsWdmVersionAvailable(6, 0x00))
		RtlInitUnicodeString(&ustrLinkName, LINK_GLOBAL_NAME);
	else
		RtlInitUnicodeString(&ustrLinkName, LINK_NAME);
	status = IoCreateSymbolicLink(&ustrLinkName, &ustrDevName);
	if (!NT_SUCCESS(status))
	{
		IoDeleteDevice(pDevObj);
		return status;
	}

	PsSetLoadImageNotifyRoutine(NotifyImageLoadCallback);

	return STATUS_SUCCESS;

}