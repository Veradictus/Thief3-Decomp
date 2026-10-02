// Game/Unsorted_10B43D80_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10B45AD0;

void* FUN_10b154c0();

class WindowManager
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4(Class_10B45AD0* Window);
};

class Class_10B45AD0
{
public:
    void FUN_10b45ad0(int A);

    char Unknown00[0x158];
    int Unknown158;
};

// FUNCTION: 0x10B45AD0 ?FUN_10b45ad0@Class_10B45AD0@@QAEXH@Z
void Class_10B45AD0::FUN_10b45ad0(int A)
{
    Unknown158 = A;
    static_cast<WindowManager*>(FUN_10b154c0())->Virtual4(this);
}
