// Game/Unsorted_10BA9FB0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10BA9FB0_Member
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4(int A);
};

struct Struct_10AA3520
{
    char Unknown00[0xB0];
    Class_10BA9FB0_Member* UnknownB0;
};

extern Struct_10AA3520* DAT_10f35dec;

class Class_10BA9FB0
{
public:
    void FUN_10ba9fb0();

    char Unknown00[0x34];
    int Unknown34;
};

// FUNCTION: 0x10BA9FB0 ?FUN_10ba9fb0@Class_10BA9FB0@@QAEXXZ
void Class_10BA9FB0::FUN_10ba9fb0()
{
    DAT_10f35dec->UnknownB0->Virtual4(Unknown34);
}
