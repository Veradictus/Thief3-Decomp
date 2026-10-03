// Game/Unsorted_10AAE2A0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct GUID
{
    unsigned long Data1;
    unsigned short Data2;
    unsigned short Data3;
    unsigned char Data4[8];
};

struct DIDEVICEINSTANCEA
{
    unsigned long dwSize;
    GUID guidInstance;
    GUID guidProduct;
    unsigned long dwDevType;
    char tszInstanceName[260];
    char tszProductName[260];
    GUID guidFFDriver;
    unsigned short wUsagePage;
    unsigned short wUsage;
};

class IDirectInputDevice8A;

class IDirectInput8A
{
public:
    virtual long __stdcall Virtual0();
    virtual long __stdcall Virtual1();
    virtual long __stdcall Virtual2();
    virtual long __stdcall CreateDevice(const GUID& Guid, IDirectInputDevice8A** Device, void* Outer);
};

int FUN_10af3690(const char* A, const char* B);

extern const char* DAT_10f3a250;

extern IDirectInput8A* DAT_10f3a36c;

extern IDirectInputDevice8A* DAT_10f3a368;

// FUNCTION: 0x10AAE2A0 ?FUN_10aae2a0@@YGHPBUDIDEVICEINSTANCEA@@PAX@Z
int __stdcall FUN_10aae2a0(const DIDEVICEINSTANCEA* Instance, void* Ref)
{
    if (FUN_10af3690(DAT_10f3a250, Instance->tszProductName) == 0)
    {
        if (DAT_10f3a36c->CreateDevice(Instance->guidInstance, &DAT_10f3a368, 0) < 0)
            DAT_10f3a368 = 0;
        return 0;
    }
    return 1;
}
