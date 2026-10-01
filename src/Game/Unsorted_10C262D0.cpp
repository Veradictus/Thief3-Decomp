// Game/Unsorted_10C262D0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Struct_10C26310
{
    int Unknown00;
    int Unknown04;
    int Unknown08;
};

struct Data_10C26310
{
    char Unknown00[0x2C];
    Struct_10C26310 Unknown2C;
    Struct_10C26310 Unknown38;
};

class Class_10c7d570
{
public:
    void* FUN_10c7d570();
};

class Class_10E99298
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
    virtual Struct_10C26310 FUN_10c26310();
    virtual Struct_10C26310 FUN_10c26340();

    char Unknown04[4];
    Class_10c7d570* Unknown08;
};

// FUNCTION: 0x10C26310 ?FUN_10c26310@Class_10E99298@@UAE?AUStruct_10C26310@@XZ
Struct_10C26310 Class_10E99298::FUN_10c26310()
{
    Data_10C26310* Data = (Data_10C26310*)Unknown08->FUN_10c7d570();
    return Data->Unknown2C;
}

// FUNCTION: 0x10C26340 ?FUN_10c26340@Class_10E99298@@UAE?AUStruct_10C26310@@XZ
Struct_10C26310 Class_10E99298::FUN_10c26340()
{
    Data_10C26310* Data = (Data_10C26310*)Unknown08->FUN_10c7d570();
    return Data->Unknown38;
}
