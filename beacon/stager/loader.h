#define PROCESS_CREATION_MITIGATION_POLICY_BLOCK_NON_MICROSOFT_BINARIES_ALWAYS_ON (0x00000001ULL << 44)
#define PROCESS_CREATION_MITIGATION_POLICY_PROHIBIT_DYNAMIC_CODE_ALWAYS_ON        (0x00000001ULL << 36)
#define PROCESS_CREATION_MITIGATION_POLICY_IMAGE_LOAD_NO_REMOTE_ALWAYS_ON         (0x00000001ULL << 52)

#define PROC_THREAD_ATTRIBUTE_NUMBER    0x0000FFFF
#define PROC_THREAD_ATTRIBUTE_THREAD    0x00010000
#define PROC_THREAD_ATTRIBUTE_INPUT     0x00020000
#define PROC_THREAD_ATTRIBUTE_ADDITIVE  0x00040000

#define ProcThreadAttributeValue(Number, Thread, Input, Additive) \
                                (((Number) & PROC_THREAD_ATTRIBUTE_NUMBER) | \
                                ((Thread != FALSE) ? PROC_THREAD_ATTRIBUTE_THREAD : 0) | \
                                ((Input != FALSE) ? PROC_THREAD_ATTRIBUTE_INPUT : 0) | \
                                ((Additive != FALSE) ? PROC_THREAD_ATTRIBUTE_ADDITIVE : 0))

#define PROC_THREAD_ATTRIBUTE_PARENT_PROCESS ProcThreadAttributeValue (0, FALSE, TRUE, FALSE)
#define PROC_THREAD_ATTRIBUTE_MITIGATION_POLICY ProcThreadAttributeValue(7, FALSE, TRUE, FALSE)

typedef struct _STARTUPINFOEXA {
  STARTUPINFOA                 StartupInfo;
  LPPROC_THREAD_ATTRIBUTE_LIST lpAttributeList;
} STARTUPINFOEXA, *LPSTARTUPINFOEXA;

typedef void (WINAPI * RtlGetVersion_) (OSVERSIONINFOEXW *);

NTSTATUS(*NtAllocateVirtualMemory)(
    HANDLE ProcessHandle, 
    PVOID *BaseAddress,
    ULONG_PTR ZeroBits,
    PSIZE_T RegionSize,
    ULONG AllocationType,
    ULONG Protect
);

NTSTATUS(*NtProtectVirtualMemory)(
    HANDLE ProcessHandle,
    PVOID *BaseAddress,
    PSIZE_T NumberOfBytesToProtect,
    ULONG NewAccessProtection,
    PULONG OldAccessProtection
);