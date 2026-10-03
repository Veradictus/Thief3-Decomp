// Game/Unsorted_10B36490.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class WindowManager;

extern WindowManager* GWindowManager;

class Class_10B17510
{
public:
    void FUN_10b17510(void* A);
};

void* FUN_10b154c0();

class Object_10B36490
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5();
    virtual void Virtual6();
    virtual void Virtual7();
    virtual void* Virtual8();
};

class Class_10E7C41C
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual int FUN_10b36490(int A, Object_10B36490* B, int C);
};

// FUNCTION: 0x10B36490 ?FUN_10b36490@Class_10E7C41C@@UAEHHPAVObject_10B36490@@H@Z
int Class_10E7C41C::FUN_10b36490(int A, Object_10B36490* B, int C)
{
    if (GWindowManager)
    {
        if (B->Virtual8())
            static_cast<Class_10B17510*>(FUN_10b154c0())->FUN_10b17510(B->Virtual8());
    }
    return 1;
}
