// Game/Class_109B5830.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Core/Core.h"

struct Info_109B5830
{
    FName Unknown00;
    char Unknown04[0x3C];
};

struct Data_109B5830
{
    char Unknown000[0x188];
    Info_109B5830* Unknown188;
};

class Class_109B5830
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
    virtual void Virtual18();
    virtual void Virtual19();
    virtual void Virtual20();
    virtual void Virtual21();
    virtual void Virtual22();
    virtual void Virtual23();
    virtual void Virtual24();
    virtual void Virtual25();
    virtual void Virtual26();
    virtual void Virtual27();
    virtual void Virtual28();
    virtual void Virtual29();
    virtual void Virtual30();
    virtual void Virtual31();
    virtual void Virtual32();
    virtual void Virtual33();
    virtual void Virtual34();
    virtual void Virtual35();
    virtual void Virtual36();
    virtual void Virtual37();
    virtual void Virtual38();
    virtual Data_109B5830* Virtual39();

    FName FUN_109b5830(int Index);
};

// FUNCTION: 0x109B5830 ?FUN_109b5830@Class_109B5830@@QAE?AVFName@@H@Z
FName Class_109B5830::FUN_109b5830(int Index)
{
    return Virtual39()->Unknown188[Index].Unknown00;
}
