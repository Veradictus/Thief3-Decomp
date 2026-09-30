// Game/Unsorted_10B4EC60.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Struct_10B4F4B0_B
{
    char Unknown00[0xC];
    int Unknown0C;
};

class Object_10B4F4B0
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5();
    virtual Struct_10B4F4B0_B* Virtual6();
};

struct Struct_10B4F4B0
{
    char Unknown00[0xB0];
    Object_10B4F4B0* UnknownB0;
};

class Class_10E7EA90
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5();
    virtual void Virtual6();
    virtual void FUN_10b4f4b0(Struct_10B4F4B0* Other);
    virtual void Virtual8(int Value);
};

// FUNCTION: 0x10B4F4B0 ?FUN_10b4f4b0@Class_10E7EA90@@UAEXPAUStruct_10B4F4B0@@@Z
void Class_10E7EA90::FUN_10b4f4b0(Struct_10B4F4B0* Other)
{
    Struct_10B4F4B0_B* Item = Other->UnknownB0->Virtual6();
    Virtual8(Item->Unknown0C);
}
