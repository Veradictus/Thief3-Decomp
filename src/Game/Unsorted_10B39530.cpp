// Game/Unsorted_10B39530.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10B481C0
{
public:
    void FUN_10b481c0(int A, float B, float C, int D, int E, int F, int G, float H);
};

class Class_10B3A460
{
public:
    Class_10B3A460* FUN_10b3a460(int A);

    char Unknown00[0x1C];
    int Unknown1C;
};

Class_10B3A460* FUN_10b3abf0();

class Class_10B39530
{
public:
    void FUN_10b39530(int A, float B, float C, int D, int E, int F, float G);

    char Unknown00[0xC];
    Class_10B481C0* Unknown0C[1];
};

// FUNCTION: 0x10B39530 ?FUN_10b39530@Class_10B39530@@QAEXHMMHHHM@Z
void Class_10B39530::FUN_10b39530(int A, float B, float C, int D, int E, int F, float G)
{
    int Index = FUN_10b3abf0()->FUN_10b3a460(A)->Unknown1C;
    Unknown0C[Index]->FUN_10b481c0(A, B, C, D, E, 0, F, G);
}
