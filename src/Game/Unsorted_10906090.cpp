// Game/Unsorted_10906090.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10905A90_Member
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5();
    virtual void Virtual6();
    virtual void Virtual7(int A);
};

Class_10905A90_Member* FUN_10905aa0();

int FUN_10901770();

void FUN_10906cb0();

void RelaunchForLevelChange();

void FUN_10918880(int A);

extern "C" __declspec(dllimport) void* __stdcall GetCurrentProcess(void);

extern "C" __declspec(dllimport) int __stdcall TerminateProcess(void* Process, unsigned int ExitCode);

extern "C" __declspec(dllimport) int __stdcall VirtualFree(void* Address, unsigned long Size, unsigned long FreeType);

extern unsigned char DAT_10f2bfec;

extern void* DAT_10f2bfe4;

extern unsigned char DAT_10f2bfed;

extern void* DAT_10f2bfe8;

// FUNCTION: 0x10906D80 ?ForceExit@@YAXXZ
void ForceExit()
{
    if (FUN_10901770())
        FUN_10905aa0()->Virtual7(0);
    FUN_10906cb0();
    RelaunchForLevelChange();
    FUN_10918880(1);
    TerminateProcess(GetCurrentProcess(), -1);
}

// FUNCTION: 0x10907190 ?FUN_10907190@@YAXXZ
void FUN_10907190()
{
    if (DAT_10f2bfec)
    {
        VirtualFree(DAT_10f2bfe4, 0, 0x8000);
        DAT_10f2bfe4 = 0;
        DAT_10f2bfec = 0;
    }
    if (DAT_10f2bfed)
    {
        VirtualFree(DAT_10f2bfe8, 0, 0x8000);
        DAT_10f2bfe8 = 0;
        DAT_10f2bfed = 0;
    }
}
