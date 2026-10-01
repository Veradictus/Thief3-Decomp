// Game/Unsorted_10BA5350.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10E8D65C
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void FUN_10ba9010(bool p1);

    char Unknown04;
    bool Unknown05;
    char Unknown06[6];
    int Unknown0C;
};

struct Struct_10BA9E70
{
    int Unknown00;
    int Unknown04;
    int Unknown08;
};

class Class_10BA9E70
{
public:
    Class_10BA9E70* FUN_10ba9e70(const Struct_10BA9E70& A, const Struct_10BA9E70& B, int C, int D, int E, int F);

    Struct_10BA9E70 Unknown00;
    Struct_10BA9E70 Unknown0C;
    int Unknown18;
    int Unknown1C;
    int Unknown20;
    int Unknown24;
};

// FUNCTION: 0x10BA9010 ?FUN_10ba9010@Class_10E8D65C@@UAEX_N@Z
void Class_10E8D65C::FUN_10ba9010(bool p1)
{
    Unknown05 = p1;
    if (!p1)
        Unknown0C = 0;
}

// FUNCTION: 0x10BA9E70 ?FUN_10ba9e70@Class_10BA9E70@@QAEPAV1@ABUStruct_10BA9E70@@0HHHH@Z
Class_10BA9E70* Class_10BA9E70::FUN_10ba9e70(const Struct_10BA9E70& A, const Struct_10BA9E70& B, int C, int D, int E,
                                             int F)
{
    Unknown00 = A;
    Unknown0C = B;
    Unknown18 = C;
    Unknown1C = D;
    Unknown20 = E;
    Unknown24 = F;
    return this;
}
