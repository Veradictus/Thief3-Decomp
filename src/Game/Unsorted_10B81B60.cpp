// Game/Unsorted_10B81B60.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Core/Core.h"

class Class_10B81B60
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
    virtual void Virtual13();
    virtual void Virtual14();
    virtual void Virtual15();
    virtual void Virtual16();
    virtual void Virtual17();
    virtual void Virtual18(int Mode, int A, int B);

    void FUN_10b81b60(int Type);

    char Unknown04[8];
    int Unknown0C;
    char Unknown10[0xE8];
    FVector Unknown0F8;
};

// FUNCTION: 0x10B81B60 ?FUN_10b81b60@Class_10B81B60@@QAEXH@Z
void Class_10B81B60::FUN_10b81b60(int Type)
{
    int Mode;
    switch (Type)
    {
    case 1:
    case 2:
        Mode = 3;
        break;
    case 3:
        Mode = 8;
        break;
    case 4:
        Mode = 2;
        break;
    case 5:
        Mode = 4;
        break;
    case 6:
        Mode = 5;
        break;
    case 7:
        Mode = 6;
        break;
    case 0:
    case 8:
    case 9:
    case 10:
        Mode = 1;
        break;
    default:
        return;
    }
    Virtual18(Mode, 0, 0);
    if (Unknown0C != 1)
        Unknown0F8 = FVector(0.0f, 0.0f, 0.0f);
}
