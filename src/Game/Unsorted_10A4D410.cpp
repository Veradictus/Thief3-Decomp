// Game/Unsorted_10A4D410.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10A4DDA0 {
public:
    void FUN_10a4dda0();

    int Unknown00;
    int Unknown04;
    int Unknown08;
};

class Class_10BFBD70
{
public:
    void FUN_10bfbd70(int Count);
};

class Class_10A4E2A0
{
public:
    void FUN_10a4e2a0(int A, Class_10BFBD70* B);
};

class Class_10A4EAE0
{
public:
    void FUN_10a4eae0(int A, Class_10BFBD70* B);

    char Unknown00[0x1C];
    Class_10A4E2A0 Unknown1C;
};

// FUNCTION: 0x10A4DDA0 ?FUN_10a4dda0@Class_10A4DDA0@@QAEXXZ
void Class_10A4DDA0::FUN_10a4dda0()
{
    Unknown00 = 0;
    Unknown04 = 0;
    Unknown08 = 0;
}

// FUNCTION: 0x10A4EAE0 ?FUN_10a4eae0@Class_10A4EAE0@@QAEXHPAVClass_10BFBD70@@@Z
void Class_10A4EAE0::FUN_10a4eae0(int A, Class_10BFBD70* B)
{
    B->FUN_10bfbd70(0);
    Unknown1C.FUN_10a4e2a0(A, B);
}
