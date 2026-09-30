// Game/Unsorted_10A0C0C0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern int DAT_10f39870;

extern int DAT_10f39874;

extern void* DAT_10f352d8;

class SomeObject {
public:
    virtual void F0() = 0;
    virtual void F1() = 0;
    virtual void F2() = 0;
    virtual void F3() = 0;
    virtual void F4() = 0;
    virtual void F5() = 0;
    virtual void F6() = 0;
};

// FUNCTION: 0x10A0DC30 ?FUN_10a0dc30@@YAXXZ
void FUN_10a0dc30()
{
    SomeObject* obj = (SomeObject*)DAT_10f352d8;
    obj->F6();
}

// FUNCTION: 0x10A0FFC0 ?FUN_10a0ffc0@@YAHXZ
int FUN_10a0ffc0()
{
    return DAT_10f39870;
}

// FUNCTION: 0x10A11EB0 ?FUN_10a11eb0@@YAHXZ
int FUN_10a11eb0()
{
    return DAT_10f39874;
}
