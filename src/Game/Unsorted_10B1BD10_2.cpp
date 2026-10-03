// Game/Unsorted_10B1BD10_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class WindowManager;

extern WindowManager* GWindowManager;

void* FUN_10b154c0();

void* FUN_10b1bde0(void* Name);

class Class_10B15960
{
public:
    void FUN_10b160b0(int A, void* Entry, bool Enable);
};

class Class_10E79488
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
    virtual void Virtual8();
    virtual void Virtual9();
    virtual void Virtual10();
    virtual void FUN_10b1be20(int A, void* Name, int Mode);
};

// FUNCTION: 0x10B1BE20 ?FUN_10b1be20@Class_10E79488@@UAEXHPAXH@Z
void Class_10E79488::FUN_10b1be20(int A, void* Name, int Mode)
{
    if (Mode != -1 && GWindowManager)
        static_cast<Class_10B15960*>(FUN_10b154c0())->FUN_10b160b0(A, FUN_10b1bde0(Name), Mode == 0);
}
