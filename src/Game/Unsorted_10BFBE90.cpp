// Game/Unsorted_10BFBE90.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10BFBE90_Element
{
public:
    virtual int Virtual0();
};

class Class_10BFBE90
{
public:
    bool FUN_10bfbe90(int A);

    char Unknown00[8];
    int Unknown08;
    char Unknown0C[4];
    Class_10BFBE90_Element** Unknown10;
};

struct Struct_10BFBFD0_Value
{
    int Unknown00;
    int Unknown04;
    int Unknown08;
};

struct Struct_10BFBFD0_Entry
{
    int Unknown00;
    int Unknown04;
    Struct_10BFBFD0_Value Unknown08;
};

class Class_10BFBFD0
{
public:
    bool FUN_10bfbfd0(Struct_10BFBFD0_Value* Out, int Key);

    char Unknown00[0x54];
    int Unknown54;
    char Unknown58[4];
    Struct_10BFBFD0_Entry* Unknown5C;
};

// FUNCTION: 0x10BFBE90 ?FUN_10bfbe90@Class_10BFBE90@@QAE_NH@Z
bool Class_10BFBE90::FUN_10bfbe90(int A)
{
    for (int i = 0; i < Unknown08; i++)
    {
        if (Unknown10[i]->Virtual0() == A)
            return true;
    }
    return false;
}

// FUNCTION: 0x10BFBFD0 ?FUN_10bfbfd0@Class_10BFBFD0@@QAE_NPAUStruct_10BFBFD0_Value@@H@Z
bool Class_10BFBFD0::FUN_10bfbfd0(Struct_10BFBFD0_Value* Out, int Key)
{
    for (int i = 0; i < Unknown54; i++)
    {
        if (Unknown5C[i].Unknown04 == Key)
        {
            *Out = Unknown5C[i].Unknown08;
            return true;
        }
    }
    return false;
}
