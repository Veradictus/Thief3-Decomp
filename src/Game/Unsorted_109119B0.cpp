// Game/Unsorted_109119B0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#define HKEY_CURRENT_USER ((HKEY)(unsigned long)0x80000001)
#define HKEY_LOCAL_MACHINE ((HKEY)(unsigned long)0x80000002)
#define ERROR_SUCCESS 0L

typedef struct HKEY__* HKEY;

extern "C" __declspec(dllimport) long __stdcall RegOpenKeyA(HKEY Key, const char* SubKey, HKEY* Result);

extern "C" __declspec(dllimport) long __stdcall RegQueryValueExA(HKEY Key, const char* ValueName, unsigned long* Reserved,
                                                                 unsigned long* Type, unsigned char* Data,
                                                                 unsigned long* DataSize);

extern "C" __declspec(dllimport) long __stdcall RegCloseKey(HKEY Key);

// Ion Storm's string (0x109081E0): a char pointer, null when default constructed.
class Class_109081E0
{
public:
    Class_109081E0() : Unknown00(0) {}
    Class_109081E0(const char* In);
    ~Class_109081E0();

    char* Unknown00;
};

extern "C" __declspec(dllimport) void* __stdcall GetCurrentProcess(void);

extern "C" __declspec(dllimport) int __stdcall FreeLibrary(void* Module);

class Class_10912800
{
public:
    void FUN_10912800();

    char Unknown00[0x18];
    int (__stdcall* Unknown18)(void* Process, unsigned int Address);
    int (__stdcall* Unknown1C)(void* Process);
    char Unknown20[4];
    void* Unknown24;
    void* Unknown28;
};

extern "C" __declspec(dllimport) int __stdcall IsBadReadPtr(const void* Pointer, unsigned int Size);

extern "C" void* memcpy(void* Dest, const void* Src, unsigned Count);

// FUNCTION: 0x10911A80 ?FUN_10911a80@@YA?AVClass_109081E0@@PBD0_N@Z
Class_109081E0 FUN_10911a80(const char* SubKey, const char* ValueName, bool LocalMachine)
{
    HKEY hKey;
    unsigned long dwSize;
    char szBuffer[512];
    if (RegOpenKeyA(LocalMachine ? HKEY_LOCAL_MACHINE : HKEY_CURRENT_USER, SubKey, &hKey) == ERROR_SUCCESS)
    {
        szBuffer[0] = 0;
        dwSize = sizeof(szBuffer);
        long Result = RegQueryValueExA(hKey, ValueName, 0, 0, (unsigned char*)szBuffer, &dwSize);
        RegCloseKey(hKey);
        if (Result == ERROR_SUCCESS)
            return Class_109081E0(szBuffer);
    }
    return Class_109081E0();
}

// FUNCTION: 0x10912800 ?FUN_10912800@Class_10912800@@QAEXXZ
void Class_10912800::FUN_10912800()
{
    if (Unknown1C)
        Unknown1C(GetCurrentProcess());
    if (Unknown24)
    {
        Unknown18(GetCurrentProcess(), 0);
        FreeLibrary(Unknown24);
        Unknown24 = 0;
    }
    if (Unknown28)
    {
        FreeLibrary(Unknown28);
        Unknown28 = 0;
    }
}

// FUNCTION: 0x10912850 ?FUN_10912850@@YGHPAXPBX0IPAI@Z
int __stdcall FUN_10912850(void* Process, const void* Address, void* Buffer, unsigned int Size, unsigned int* BytesRead)
{
    if (IsBadReadPtr(Address, Size))
        return 0;
    memcpy(Buffer, Address, Size);
    if (BytesRead)
        *BytesRead = Size;
    return 1;
}
