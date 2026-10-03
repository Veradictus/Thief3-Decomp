// Game/Unsorted_10B98C90.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern float DAT_10eafbdc;

int FUN_10be2e50();

class Class_10BBDB40
{
public:
    float FUN_10bbdb40();
};

class Class_10DBD510
{
public:
    Class_10BBDB40* FUN_10dbd510(int Id);
};

struct Struct_10B98C90
{
    char Unknown00[8];
    Class_10DBD510* Unknown08;
};

// FUNCTION: 0x10B98C90 ?FUN_10b98c90@@YAHPAUStruct_10B98C90@@@Z
int FUN_10b98c90(Struct_10B98C90* P)
{
    int Id = FUN_10be2e50();
    if (Id)
    {
        Class_10DBD510* Owner = P->Unknown08;
        if (Owner->FUN_10dbd510(Id)->FUN_10bbdb40() > DAT_10eafbdc)
            return 1;
    }
    return 0;
}
