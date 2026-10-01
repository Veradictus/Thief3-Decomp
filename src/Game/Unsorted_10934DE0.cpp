// Game/Unsorted_10934DE0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10955DB0
{
public:
    void FUN_10955db0(int A, int B, int C);
};

struct Struct_10934FE0
{
    char Unknown00[0x4C];
    bool Unknown4C;
    char Unknown4D[0x43];
    Class_10955DB0 Unknown90;
};

class Class_10E49F90
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5();
    virtual bool FUN_10934fe0(Struct_10934FE0* P, int B);
};

class Class_10936870
{
public:
    char Unknown00[0x6b4];
    unsigned int Unknown6b4;

    void FUN_10936870(unsigned int Flags);
};

// FUNCTION: 0x10934FE0 ?FUN_10934fe0@Class_10E49F90@@UAE_NPAUStruct_10934FE0@@H@Z
bool Class_10E49F90::FUN_10934fe0(Struct_10934FE0* P, int B)
{
    if (P->Unknown4C)
        P->Unknown90.FUN_10955db0(2, 0, 1);
    return true;
}

// FUNCTION: 0x10936870 ?FUN_10936870@Class_10936870@@QAEXI@Z
void Class_10936870::FUN_10936870(unsigned int Flags)
{
    Unknown6b4 |= Flags;
}
