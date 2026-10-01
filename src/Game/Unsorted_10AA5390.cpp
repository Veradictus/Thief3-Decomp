// Game/Unsorted_10AA5390.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Struct_10AA53E0_Item
{
    char Unknown00[0x1C];
};

class Class_10E6D600
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual Struct_10AA53E0_Item* FUN_10aa53e0(int A);
    virtual Struct_10AA53E0_Item* Virtual6(int A);

    int Unknown04;
    int Unknown08;
    int Unknown0C;
    Struct_10AA53E0_Item* Unknown10;
};

// FUNCTION: 0x10AA53E0 ?FUN_10aa53e0@Class_10E6D600@@UAEPAUStruct_10AA53E0_Item@@H@Z
Struct_10AA53E0_Item* Class_10E6D600::FUN_10aa53e0(int A)
{
    return &Unknown10[(Unknown04 + A) % Unknown08];
}
