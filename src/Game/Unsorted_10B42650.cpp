// Game/Unsorted_10B42650.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

void FUN_10a683d0(int A, int B, int C, int D, int E);

struct Struct_10B42650
{
    char Unknown00[0xC];
    char Unknown0C[0xC];
    int Unknown18;
};

class Class_10B42640
{
public:
    void FUN_10b42650(int A, int B);

    char Unknown00[0x1C];
    int Count;
    char Unknown20[4];
    Struct_10B42650* Data;
};

// FUNCTION: 0x10B42650 ?FUN_10b42650@Class_10B42640@@QAEXHH@Z
void Class_10B42640::FUN_10b42650(int A, int B)
{
    for (int i = 0; i < Count; i++)
        FUN_10a683d0(A, B, (int)&Data[i], (int)&Data[i].Unknown0C, (int)&Data[i].Unknown18);
}
