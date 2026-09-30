// Game/Unsorted_10C1ABD0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Struct_10C1ABD0
{
    int Unknown00;
    int Unknown04;
    int Unknown08;
};

class Class_10E98E70
{
public:
    virtual void Virtual0();
    virtual bool FUN_10c1abd0(Struct_10C1ABD0* Out, int* Value);

    char Unknown04[0x44];
    Struct_10C1ABD0 Unknown48;
    int Unknown54;
};

class Class_10c1ac00
{
public:
    char Unknown00[0x58];
    int Unknown58;
    int* FUN_10c1ac00(int* p1);
};

// FUNCTION: 0x10C1ABD0 ?FUN_10c1abd0@Class_10E98E70@@UAE_NPAUStruct_10C1ABD0@@PAH@Z
bool Class_10E98E70::FUN_10c1abd0(Struct_10C1ABD0* Out, int* Value)
{
    *Out = Unknown48;
    *Value = Unknown54;
    return true;
}

// FUNCTION: 0x10C1AC00 ?FUN_10c1ac00@Class_10c1ac00@@QAEPAHPAH@Z
int* Class_10c1ac00::FUN_10c1ac00(int* p1)
{
    *p1 = Unknown58;
    return p1;
}
