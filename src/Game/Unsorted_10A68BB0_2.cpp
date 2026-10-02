// Game/Unsorted_10A68BB0_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern "C" void* memcpy(void* Dest, const void* Src, unsigned Count);

struct Struct_10A68BB0
{
    char Unknown00[0x10];
};

class Class_10953AC0
{
public:
    void FUN_10953ac0(int A);

    char Unknown00[8];
    char* Unknown08;
};

class Class_10E6B5A0
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual int FUN_10a68bb0(const Struct_10A68BB0* Items, int Count);

    char Unknown04[0xC];
    int Unknown10;
    Class_10953AC0 Unknown14;
};

// FUNCTION: 0x10A68BB0 ?FUN_10a68bb0@Class_10E6B5A0@@UAEHPBUStruct_10A68BB0@@H@Z
int Class_10E6B5A0::FUN_10a68bb0(const Struct_10A68BB0* Items, int Count)
{
    Unknown14.FUN_10953ac0(Count);
    memcpy(Unknown14.Unknown08, Items, Count * sizeof(Struct_10A68BB0));
    return ++Unknown10;
}
