// Game/Unsorted_10B396B0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_Field04
{
public:
    void FUN_10b476d0();
};

class Class_10B3A460
{
public:
    Class_10B3A460* FUN_10b3a460(int Index);

    char Unknown00[0x1C];
    int Unknown1C;
    char Unknown20[0xC];
};

Class_10B3A460* FUN_10b3abf0();

class Class_10B396B0
{
public:
    void FUN_10b396b0(int A);

    char Unknown00[0xC];
    Class_Field04* Unknown0C[1];
};

class Class_10B396E0
{
public:
    void FUN_10b396e0();

    char Unknown00[0xC];
    Class_Field04* Unknown0C[8];
};

// FUNCTION: 0x10B396B0 ?FUN_10b396b0@Class_10B396B0@@QAEXH@Z
void Class_10B396B0::FUN_10b396b0(int A)
{
    int Index = FUN_10b3abf0()->FUN_10b3a460(A)->Unknown1C;
    Unknown0C[Index]->FUN_10b476d0();
}

// FUNCTION: 0x10B396E0 ?FUN_10b396e0@Class_10B396E0@@QAEXXZ
void Class_10B396E0::FUN_10b396e0()
{
    for (int i = 0; i < 8; i++)
        Unknown0C[i]->FUN_10b476d0();
}
