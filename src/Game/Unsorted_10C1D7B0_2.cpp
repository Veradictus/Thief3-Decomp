// Game/Unsorted_10C1D7B0_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10E991C4;

class Class_10BAE580
{
public:
    void FUN_10bae580(int A, Class_10E991C4* B);
};

class Class_10DC1750_Result
{
public:
    char Unknown00[0x1C];
    Class_10BAE580 Unknown1C;
};

class Class_10DC1750
{
public:
    Class_10DC1750_Result* FUN_10dc1750();
};

class Class_10E991C4
{
public:
    virtual void Virtual0();
    virtual void FUN_10c1f420(int A);

    Class_10DC1750* Unknown04;
};

class Class_10FF667C
{
public:
    char Unknown00[0x6C];
    int Unknown6C;
    int Unknown70;
    int Unknown74;
};

extern Class_10FF667C* DAT_10ff667c;

struct Struct_10C1F4D0
{
    int Unknown00;
};

class Class_10C1F4D0
{
public:
    int FUN_10c1f4d0(Struct_10C1F4D0* A);
};

// FUNCTION: 0x10C1F420 ?FUN_10c1f420@Class_10E991C4@@UAEXH@Z
void Class_10E991C4::FUN_10c1f420(int A)
{
    Class_10DC1750_Result* Result = Unknown04->FUN_10dc1750();
    Result->Unknown1C.FUN_10bae580(A, this);
}

// FUNCTION: 0x10C1F4D0 ?FUN_10c1f4d0@Class_10C1F4D0@@QAEHPAUStruct_10C1F4D0@@@Z
int Class_10C1F4D0::FUN_10c1f4d0(Struct_10C1F4D0* A)
{
    int Kind = A->Unknown00;
    if (Kind == DAT_10ff667c->Unknown6C || Kind == DAT_10ff667c->Unknown70 || Kind == DAT_10ff667c->Unknown74)
        return 1;
    return 0;
}
