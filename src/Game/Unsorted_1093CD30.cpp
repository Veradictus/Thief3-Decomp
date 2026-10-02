// Game/Unsorted_1093CD30.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_1093E930_Member
{
public:
    virtual int __stdcall Virtual0();
    virtual int __stdcall Virtual1();
    virtual int __stdcall Virtual2();
};

class Class_1093E930
{
public:
    void FUN_1093e550();

    Class_1093E930_Member* Unknown00;
    Class_1093E930_Member* Unknown04;
    bool Unknown08;
};

// FUNCTION: 0x1093E550 ?FUN_1093e550@Class_1093E930@@QAEXXZ
void Class_1093E930::FUN_1093e550()
{
    if (Unknown00)
    {
        Unknown00->Virtual2();
        Unknown00 = 0;
    }
    if (Unknown04)
    {
        Unknown04->Virtual2();
        Unknown04 = 0;
    }
    Unknown08 = false;
}
