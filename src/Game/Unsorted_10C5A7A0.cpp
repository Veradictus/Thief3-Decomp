// Game/Unsorted_10C5A7A0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10C5B8F0_Member
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
    virtual void Virtual11();
    virtual void Virtual12();
    virtual void Virtual13(int A);
};

struct Struct_10AA3520
{
    char Unknown00[0xBC];
    Class_10C5B8F0_Member* UnknownBC;
};

extern Struct_10AA3520* DAT_10f35dec;

// FUNCTION: 0x10C5B8F0 ?FUN_10c5b8f0@@YGXH@Z
void __stdcall FUN_10c5b8f0(int A)
{
    if (DAT_10f35dec)
    {
        Class_10C5B8F0_Member* Obj = DAT_10f35dec->UnknownBC;
        if (Obj)
            Obj->Virtual13(A);
    }
}
