#if !defined(_IO_CONTROLLER_DEFINED_)

#define _IO_CONTROLLER_DEFINED_

#include  "Objects.h"
#include "Process ctl codes.h"

/* EPROCESS STRUCTURES WIN 10 OFFSETS */
// 0x2E8 UniqueProcessId
// 0x2F0 ActiveProcessLink

#define GET_RECORD(Start, Offset, TypeCast)((TypeCast)((Start + Offset)))

NTSTATUS IoControl(PDEVICE_OBJECT pDeviceObject, PIRP pIrp)
{
	PIO_STACK_LOCATION StackLocation = IoGetCurrentIrpStackLocation(pIrp);

	ULONG ControlCode = StackLocation->Parameters.DeviceIoControl.IoControlCode;

	NTSTATUS Status;

	if (ControlCode == GET_PID_LIST)
	{
		PPID_LIST PidListOut = (PPID_LIST)pIrp->AssociatedIrp.SystemBuffer;

		PEPROCESS StartProcess = PsGetCurrentProcess();

		PLIST_ENTRY HeadList = (PLIST_ENTRY)((INT)StartProcess + 0x2F0);

		DbgPrint("List entry Blink: %llu", HeadList->Blink);
		DbgPrint("List entry Flink: %llu", HeadList->Flink);

		pIrp->IoStatus.Status = STATUS_SUCCESS;
		pIrp->IoStatus.Information = 0;
	}
	else
	{
		Status = STATUS_INVALID_PARAMETER;
		pIrp->IoStatus.Information = 0;
		pIrp->IoStatus.Status = Status;
	}

	IoCompleteRequest(pIrp, IO_NO_INCREMENT);
	return Status;
}

#endif

/*

ntdll!_EPROCESS
+0x000 Pcb              : _KPROCESS
+0x2d8 ProcessLock      : _EX_PUSH_LOCK
+0x2e0 RundownProtect   : _EX_RUNDOWN_REF
+0x2e8 UniqueProcessId  : Ptr64 Void
+0x2f0 ActiveProcessLinks : _LIST_ENTRY
+0x300 Flags2           : Uint4B
+0x300 JobNotReallyActive : Pos 0, 1 Bit
+0x300 AccountingFolded : Pos 1, 1 Bit
+0x300 NewProcessReported : Pos 2, 1 Bit
+0x300 ExitProcessReported : Pos 3, 1 Bit
+0x300 ReportCommitChanges : Pos 4, 1 Bit
+0x300 LastReportMemory : Pos 5, 1 Bit
+0x300 ForceWakeCharge  : Pos 6, 1 Bit
+0x300 CrossSessionCreate : Pos 7, 1 Bit
+0x300 NeedsHandleRundown : Pos 8, 1 Bit
+0x300 RefTraceEnabled  : Pos 9, 1 Bit
+0x300 DisableDynamicCode : Pos 10, 1 Bit
+0x300 EmptyJobEvaluated : Pos 11, 1 Bit
+0x300 DefaultPagePriority : Pos 12, 3 Bits
+0x300 PrimaryTokenFrozen : Pos 15, 1 Bit
+0x300 ProcessVerifierTarget : Pos 16, 1 Bit
+0x300 StackRandomizationDisabled : Pos 17, 1 Bit
+0x300 AffinityPermanent : Pos 18, 1 Bit
+0x300 AffinityUpdateEnable : Pos 19, 1 Bit
+0x300 PropagateNode    : Pos 20, 1 Bit
+0x300 ExplicitAffinity : Pos 21, 1 Bit
+0x300 ProcessExecutionState : Pos 22, 2 Bits
+0x300 DisallowStrippedImages : Pos 24, 1 Bit
+0x300 HighEntropyASLREnabled : Pos 25, 1 Bit
+0x300 ExtensionPointDisable : Pos 26, 1 Bit
+0x300 ForceRelocateImages : Pos 27, 1 Bit
+0x300 ProcessStateChangeRequest : Pos 28, 2 Bits
+0x300 ProcessStateChangeInProgress : Pos 30, 1 Bit
+0x300 DisallowWin32kSystemCalls : Pos 31, 1 Bit
+0x304 Flags            : Uint4B
+0x304 CreateReported   : Pos 0, 1 Bit
+0x304 NoDebugInherit   : Pos 1, 1 Bit
+0x304 ProcessExiting   : Pos 2, 1 Bit
+0x304 ProcessDelete    : Pos 3, 1 Bit
+0x304 ControlFlowGuardEnabled : Pos 4, 1 Bit
+0x304 VmDeleted        : Pos 5, 1 Bit
+0x304 OutswapEnabled   : Pos 6, 1 Bit
+0x304 Outswapped       : Pos 7, 1 Bit
+0x304 FailFastOnCommitFail : Pos 8, 1 Bit
+0x304 Wow64VaSpace4Gb  : Pos 9, 1 Bit
+0x304 AddressSpaceInitialized : Pos 10, 2 Bits
+0x304 SetTimerResolution : Pos 12, 1 Bit
+0x304 BreakOnTermination : Pos 13, 1 Bit
+0x304 DeprioritizeViews : Pos 14, 1 Bit
+0x304 WriteWatch       : Pos 15, 1 Bit
+0x304 ProcessInSession : Pos 16, 1 Bit
+0x304 OverrideAddressSpace : Pos 17, 1 Bit
+0x304 HasAddressSpace  : Pos 18, 1 Bit
+0x304 LaunchPrefetched : Pos 19, 1 Bit
+0x304 Background       : Pos 20, 1 Bit
+0x304 VmTopDown        : Pos 21, 1 Bit
+0x304 ImageNotifyDone  : Pos 22, 1 Bit
+0x304 PdeUpdateNeeded  : Pos 23, 1 Bit
+0x304 VdmAllowed       : Pos 24, 1 Bit
+0x304 ProcessRundown   : Pos 25, 1 Bit
+0x304 ProcessInserted  : Pos 26, 1 Bit
+0x304 DefaultIoPriority : Pos 27, 3 Bits
+0x304 ProcessSelfDelete : Pos 30, 1 Bit
+0x304 SetTimerResolutionLink : Pos 31, 1 Bit
+0x308 CreateTime       : _LARGE_INTEGER
+0x310 ProcessQuotaUsage : [2] Uint8B
+0x320 ProcessQuotaPeak : [2] Uint8B
+0x330 PeakVirtualSize  : Uint8B
+0x338 VirtualSize      : Uint8B
+0x340 SessionProcessLinks : _LIST_ENTRY
+0x350 ExceptionPortData : Ptr64 Void
+0x350 ExceptionPortValue : Uint8B
+0x350 ExceptionPortState : Pos 0, 3 Bits
+0x358 Token            : _EX_FAST_REF
+0x360 WorkingSetPage   : Uint8B
+0x368 AddressCreationLock : _EX_PUSH_LOCK
+0x370 PageTableCommitmentLock : _EX_PUSH_LOCK
+0x378 RotateInProgress : Ptr64 _ETHREAD
+0x380 ForkInProgress   : Ptr64 _ETHREAD
+0x388 CommitChargeJob  : Ptr64 _EJOB
+0x390 CloneRoot        : _RTL_AVL_TREE
+0x398 NumberOfPrivatePages : Uint8B
+0x3a0 NumberOfLockedPages : Uint8B
+0x3a8 Win32Process     : Ptr64 Void
+0x3b0 Job              : Ptr64 _EJOB
+0x3b8 SectionObject    : Ptr64 Void
+0x3c0 SectionBaseAddress : Ptr64 Void
+0x3c8 Cookie           : Uint4B
+0x3d0 WorkingSetWatch  : Ptr64 _PAGEFAULT_HISTORY
+0x3d8 Win32WindowStation : Ptr64 Void
+0x3e0 InheritedFromUniqueProcessId : Ptr64 Void
+0x3e8 LdtInformation   : Ptr64 Void
+0x3f0 OwnerProcessId   : Uint8B
+0x3f8 Peb              : Ptr64 _PEB
+0x400 Session          : Ptr64 Void
+0x408 AweInfo          : Ptr64 Void
+0x410 QuotaBlock       : Ptr64 _EPROCESS_QUOTA_BLOCK
+0x418 ObjectTable      : Ptr64 _HANDLE_TABLE
+0x420 DebugPort        : Ptr64 Void
+0x428 Wow64Process     : Ptr64 Void
+0x430 DeviceMap        : Ptr64 Void
+0x438 EtwDataSource    : Ptr64 Void
+0x440 PageDirectoryPte : Uint8B
+0x448 ImageFileName    : [15] UChar
+0x457 PriorityClass    : UChar
+0x458 SecurityPort     : Ptr64 Void
+0x460 SeAuditProcessCreationInfo : _SE_AUDIT_PROCESS_CREATION_INFO
+0x468 JobLinks         : _LIST_ENTRY
+0x478 HighestUserAddress : Ptr64 Void
+0x480 ThreadListHead   : _LIST_ENTRY
+0x490 ActiveThreads    : Uint4B
+0x494 ImagePathHash    : Uint4B
+0x498 DefaultHardErrorProcessing : Uint4B
+0x49c LastThreadExitStatus : Int4B
+0x4a0 PrefetchTrace    : _EX_FAST_REF
+0x4a8 LockedPagesList  : Ptr64 Void
+0x4b0 ReadOperationCount : _LARGE_INTEGER
+0x4b8 WriteOperationCount : _LARGE_INTEGER
+0x4c0 OtherOperationCount : _LARGE_INTEGER
+0x4c8 ReadTransferCount : _LARGE_INTEGER
+0x4d0 WriteTransferCount : _LARGE_INTEGER
+0x4d8 OtherTransferCount : _LARGE_INTEGER
+0x4e0 CommitChargeLimit : Uint8B
+0x4e8 CommitCharge     : Uint8B
+0x4f0 CommitChargePeak : Uint8B
+0x4f8 Vm               : _MMSUPPORT
+0x5f0 MmProcessLinks   : _LIST_ENTRY
+0x600 ModifiedPageCount : Uint4B
+0x604 ExitStatus       : Int4B
+0x608 VadRoot          : _RTL_AVL_TREE
+0x610 VadHint          : Ptr64 Void
+0x618 VadCount         : Uint8B
+0x620 VadPhysicalPages : Uint8B
+0x628 VadPhysicalPagesLimit : Uint8B
+0x630 AlpcContext      : _ALPC_PROCESS_CONTEXT
+0x650 TimerResolutionLink : _LIST_ENTRY
+0x660 TimerResolutionStackRecord : Ptr64 _PO_DIAG_STACK_RECORD
+0x668 RequestedTimerResolution : Uint4B
+0x66c SmallestTimerResolution : Uint4B
+0x670 ExitTime         : _LARGE_INTEGER
+0x678 InvertedFunctionTable : Ptr64 _INVERTED_FUNCTION_TABLE
+0x680 InvertedFunctionTableLock : _EX_PUSH_LOCK
+0x688 ActiveThreadsHighWatermark : Uint4B
+0x68c LargePrivateVadCount : Uint4B
+0x690 ThreadListLock   : _EX_PUSH_LOCK
+0x698 WnfContext       : Ptr64 Void
+0x6a0 Spare0           : Uint8B
+0x6a8 SignatureLevel   : UChar
+0x6a9 SectionSignatureLevel : UChar
+0x6aa Protection       : _PS_PROTECTION
+0x6ab HangCount        : UChar
+0x6ac Flags3           : Uint4B
+0x6ac Minimal          : Pos 0, 1 Bit
+0x6ac ReplacingPageRoot : Pos 1, 1 Bit
+0x6ac DisableNonSystemFonts : Pos 2, 1 Bit
+0x6ac AuditNonSystemFontLoading : Pos 3, 1 Bit
+0x6ac Crashed          : Pos 4, 1 Bit
+0x6ac JobVadsAreTracked : Pos 5, 1 Bit
+0x6ac VadTrackingDisabled : Pos 6, 1 Bit
+0x6ac AuxiliaryProcess : Pos 7, 1 Bit
+0x6ac SubsystemProcess : Pos 8, 1 Bit
+0x6ac IndirectCpuSets  : Pos 9, 1 Bit
+0x6ac InPrivate        : Pos 10, 1 Bit
+0x6b0 DeviceAsid       : Int4B
+0x6b8 SvmData          : Ptr64 Void
+0x6c0 SvmProcessLock   : _EX_PUSH_LOCK
+0x6c8 SvmLock          : Uint8B
+0x6d0 SvmProcessDeviceListHead : _LIST_ENTRY
+0x6e0 LastFreezeInterruptTime : Uint8B
+0x6e8 DiskCounters     : Ptr64 _PROCESS_DISK_COUNTERS
+0x6f0 PicoContext      : Ptr64 Void
+0x6f8 TrustletIdentity : Uint8B
+0x700 KeepAliveCounter : Uint4B
+0x704 NoWakeKeepAliveCounter : Uint4B
+0x708 HighPriorityFaultsAllowed : Uint4B
+0x710 EnergyValues     : Ptr64 _PROCESS_ENERGY_VALUES
+0x718 VmContext        : Ptr64 Void
+0x720 Silo             : Ptr64 _ESILO
+0x728 SiloEntry        : _LIST_ENTRY
+0x738 SequenceNumber   : Uint8B
+0x740 CreateInterruptTime : Uint8B
+0x748 CreateUnbiasedInterruptTime : Uint8B
+0x750 TotalUnbiasedFrozenTime : Uint8B
+0x758 LastAppStateUpdateTime : Uint8B
+0x760 LastAppStateUptime : Pos 0, 61 Bits
+0x760 LastAppState     : Pos 61, 3 Bits
+0x768 SharedCommitCharge : Uint8B
+0x770 SharedCommitLock : _EX_PUSH_LOCK
+0x778 SharedCommitLinks : _LIST_ENTRY
+0x788 AllowedCpuSets   : Uint8B
+0x790 DefaultCpuSets   : Uint8B
+0x788 AllowedCpuSetsIndirect : Ptr64 Uint8B
+0x790 DefaultCpuSetsIndirect : Ptr64 Uint8B


*/