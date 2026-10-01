// Game/Unsorted_10A4EB10.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10A243F0
{
public:
    void FUN_10a243f0(int Count);
};

class Class_10A4E320
{
public:
    void FUN_10a4e320(int A, int B, Class_10A243F0* C);
};

class Class_10A4EB10
{
public:
    void FUN_10a4eb10(int A, int B, Class_10A243F0* C);

    char Unknown00[0x1C];
    Class_10A4E320 Unknown1C;
};

// FUNCTION: 0x10A4EB10 ?FUN_10a4eb10@Class_10A4EB10@@QAEXHHPAVClass_10A243F0@@@Z
void Class_10A4EB10::FUN_10a4eb10(int A, int B, Class_10A243F0* C)
{
    C->FUN_10a243f0(0);
    Unknown1C.FUN_10a4e320(A, B, C);
}
