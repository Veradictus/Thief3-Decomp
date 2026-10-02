// Game/Unsorted_10B36450.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class WindowManager;

extern WindowManager* GWindowManager;

void* FUN_10b154c0();

class Class_10B15960
{
public:
    bool FUN_10b15960(int A);
};

class Class_10E7C410
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual int FUN_10b36450(int A, int B, int C);
};

// FUNCTION: 0x10B36450 ?FUN_10b36450@Class_10E7C410@@UAEHHHH@Z
int Class_10E7C410::FUN_10b36450(int A, int B, int C)
{
    if (GWindowManager)
        ((Class_10B15960*)FUN_10b154c0())->FUN_10b15960(0);
    return 1;
}
