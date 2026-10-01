// Game/Unsorted_10BAD950.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10A68D20;

void FUN_10a68cf0(Class_10A68D20* Owner, int A, int B, int C);

class Class_10E8D7B0
{
public:
    virtual void FUN_10bad950(Class_10A68D20* Owner);

    char Unknown04[4];
    int Unknown08;
    char Unknown0C[8];
    int Unknown14;
    char Unknown18[8];
    int Unknown20;
};

// FUNCTION: 0x10BAD950 ?FUN_10bad950@Class_10E8D7B0@@UAEXPAVClass_10A68D20@@@Z
void Class_10E8D7B0::FUN_10bad950(Class_10A68D20* Owner)
{
    FUN_10a68cf0(Owner, (int)&Unknown08, (int)&Unknown14, (int)&Unknown20);
}
