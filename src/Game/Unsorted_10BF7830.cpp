// Game/Unsorted_10BF7830.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Struct_10BF7990
{
    char Unknown00[8];
    int Unknown08;
};

struct Struct_10C7D570
{
    char Unknown00[0x34];
    int Unknown34;
};

class Class_Field0C
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual bool Virtual3(Struct_10BF7990* A);
};

class Class_10c7d570
{
public:
    void* FUN_10c7d570();
};

class Class_10BF7990
{
public:
    bool FUN_10bf7990(Struct_10BF7990* A);

    char Unknown00[0xC];
    Class_Field0C* Unknown0C;
    char Unknown10[4];
    Class_10c7d570* Unknown14;
};

// FUNCTION: 0x10BF7990 ?FUN_10bf7990@Class_10BF7990@@QAE_NPAUStruct_10BF7990@@@Z
bool Class_10BF7990::FUN_10bf7990(Struct_10BF7990* A)
{
    if (!Unknown0C)
        return false;
    bool Result = Unknown0C->Virtual3(A);
    Struct_10C7D570* Obj = (Struct_10C7D570*)Unknown14->FUN_10c7d570();
    A->Unknown08 = Obj->Unknown34;
    return Result;
}
