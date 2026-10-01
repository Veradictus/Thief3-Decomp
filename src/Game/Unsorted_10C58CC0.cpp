// Game/Unsorted_10C58CC0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Struct_10C58E50
{
    ~Struct_10C58E50();

    int Unknown00;
    int Unknown04;
    int Unknown08;
    int Unknown0C;
};

class Class_10C58460
{
public:
    Struct_10C58E50 FUN_10c58460(int B, int C, int D, int E, int F, void* G, void* H);
};

class Class_10C58E50
{
public:
    Struct_10C58E50 FUN_10c58e50(int B, int C, int D, int E, int F);

    Class_10C58460* Unknown00;
};

// FUNCTION: 0x10C58E50 ?FUN_10c58e50@Class_10C58E50@@QAE?AUStruct_10C58E50@@HHHHH@Z
Struct_10C58E50 Class_10C58E50::FUN_10c58e50(int B, int C, int D, int E, int F)
{
    return Unknown00->FUN_10c58460(B, C, D, E, F, 0, 0);
}
