// Game/Unsorted_10901D60_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern const char DAT_10e47660[];

class Class_109022E0 {
public:
    char* Unknown00;
    const char* FUN_109022e0();
};

class Class_10905A90_Member {
public:
    virtual void F0() = 0;
    virtual void F1() = 0;
};

Class_10905A90_Member* FUN_10905aa0();

extern "C" __declspec(dllimport) int __stdcall CloseHandle(void* Object);

class Class_10905E60
{
public:
    void FUN_10905e60();

    char Unknown00[0x10C];
    void* Handle;
};

class Class_10905e90
{
public:
    char Unknown00[0x10c];
    int Unknown10c;
    unsigned char Unknown110;

    Class_10905e90* FUN_10905e90(int p1);
};

class Class_10905F10
{
public:
    void FUN_10905f10();

    char Unknown00[0x10C];
    void* Handle;
};

// FUNCTION: 0x109022E0 ?FUN_109022e0@Class_109022E0@@QAEPBDXZ
const char* Class_109022E0::FUN_109022e0()
{
    return Unknown00 ? Unknown00 : DAT_10e47660;
}

// FUNCTION: 0x10905A90 ?FUN_10905a90@@YAXXZ
void FUN_10905a90()
{
    FUN_10905aa0()->F1();
}

// FUNCTION: 0x10905E60 ?FUN_10905e60@Class_10905E60@@QAEXXZ
void Class_10905E60::FUN_10905e60()
{
    if (Handle != (void*)-1)
    {
        CloseHandle(Handle);
        Handle = (void*)-1;
    }
}

// FUNCTION: 0x10905E90 ?FUN_10905e90@Class_10905e90@@QAEPAV1@H@Z
Class_10905e90* Class_10905e90::FUN_10905e90(int p1)
{
    Unknown10c = -1;
    Unknown110 = 0;
    return this;
}

// FUNCTION: 0x10905F10 ?FUN_10905f10@Class_10905F10@@QAEXXZ
void Class_10905F10::FUN_10905f10()
{
    if (Handle != (void*)-1)
    {
        CloseHandle(Handle);
        Handle = (void*)-1;
    }
    Handle = (void*)-1;
}
