// Game/Unsorted_10B55030_3.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Info_10B554A0
{
    float Unknown00;
    float Unknown04;
    float Unknown08;
};

class Object_10B554A0
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2(void* A, Info_10B554A0* B);
};

struct Struct_10AA3520
{
    char Unknown00[0xB0];
    Object_10B554A0* UnknownB0;
};

extern Struct_10AA3520* DAT_10f35dec;

class Class_10B3AC90
{
public:
    void* FUN_10b3ac90();
};

struct Static_10B3AC60 : Class_10B3AC90
{
};

Static_10B3AC60* FUN_10b3ac60();

// FUNCTION: 0x10B554A0 ?FUN_10b554a0@@YAHXZ
int FUN_10b554a0()
{
    Info_10B554A0 Info;
    DAT_10f35dec->UnknownB0->Virtual2(FUN_10b3ac60()->FUN_10b3ac90(), &Info);
    return (int)Info.Unknown04;
}
