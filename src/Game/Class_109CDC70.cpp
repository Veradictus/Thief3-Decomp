// Game/Class_109CDC70.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Core/Core.h"

struct Info_109CDC70
{
    char Unknown00[0x34];
};

struct Data_109CDC70
{
    char Unknown000[0x120];
    TArray<Info_109CDC70> Unknown120;
};

class Class_109CDC70
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
    virtual Data_109CDC70* Virtual39();

    Info_109CDC70* FUN_109cdc70(int Index);
};

// FUNCTION: 0x109CDC70 ?FUN_109cdc70@Class_109CDC70@@QAEPAUInfo_109CDC70@@H@Z
Info_109CDC70* Class_109CDC70::FUN_109cdc70(int Index)
{
    return &Virtual39()->Unknown120(Index);
}
