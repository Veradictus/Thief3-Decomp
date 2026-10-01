// Game/Unsorted_10A68B80.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Struct_10A68B80
{
    int Unknown00;
    int Unknown04;
    int Unknown08;
    int Unknown0C;
};

class Class_10E6B5A0
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void FUN_10a68b80(int Index, const Struct_10A68B80& Value);

    int Unknown04;
    int Unknown08;
    int Unknown0C;
    int Unknown10;
    int Unknown14;
    int Unknown18;
    Struct_10A68B80* Unknown1C;
};

class Class_10A68D20
{
public:
    int Unknown00;
    int Unknown04;
    int Unknown08;
};

void FUN_10a68270(int A, int B, int C, int D, int E, int F);

void FUN_10a68400(int A, int B, int C, int D, int E);

void FUN_10a68590(int A, int B, int C, int D, int E, int F);

struct Struct_10A68D80
{
    int Unknown00;
    int Unknown04;
    int Unknown08;
};

void FUN_10a68600(int A, int B, int C, int D, int E, int F);

// FUNCTION: 0x10A68B80 ?FUN_10a68b80@Class_10E6B5A0@@UAEXHABUStruct_10A68B80@@@Z
void Class_10E6B5A0::FUN_10a68b80(int Index, const Struct_10A68B80& Value)
{
    Unknown1C[Index] = Value;
    Unknown10++;
}

// FUNCTION: 0x10A68CF0 ?FUN_10a68cf0@@YAXPAVClass_10A68D20@@HHH@Z
void FUN_10a68cf0(Class_10A68D20* Owner, int A, int B, int C)
{
    FUN_10a68270(Owner->Unknown04, Owner->Unknown08, A, B, C, 0);
}

// FUNCTION: 0x10A68D20 ?FUN_10a68d20@@YAXPAVClass_10A68D20@@HHH@Z
void FUN_10a68d20(Class_10A68D20* Owner, int A, int B, int C)
{
    FUN_10a68400(Owner->Unknown04, Owner->Unknown08, A, B, C);
}

// FUNCTION: 0x10A68D50 ?FUN_10a68d50@@YAXPAVClass_10A68D20@@HHHH@Z
void FUN_10a68d50(Class_10A68D20* Owner, int A, int B, int C, int D)
{
    FUN_10a68590(Owner->Unknown00, Owner->Unknown08, A, B, C, D);
}

// FUNCTION: 0x10A68D80 ?FUN_10a68d80@@YAXPAUStruct_10A68D80@@HHHH@Z
void FUN_10a68d80(Struct_10A68D80* Obj, int A, int B, int C, int D)
{
    FUN_10a68600(A, B, Obj->Unknown04, Obj->Unknown08, C, D);
}
