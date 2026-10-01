// Game/Unsorted_1095BC80.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_1095BF50;

struct Arg_1095BEF0
{
    char Unknown00;
};

void FUN_1095bef0(int A, int B, int C, Class_1095BF50* Owner, Arg_1095BEF0 Flags);

class Class_1095BF50
{
public:
    void FUN_1095bf50(int A, int B, int C);
};

// FUNCTION: 0x1095BF50 ?FUN_1095bf50@Class_1095BF50@@QAEXHHH@Z
void Class_1095BF50::FUN_1095bf50(int A, int B, int C)
{
    Arg_1095BEF0 Flags;
    Flags.Unknown00 = 0;
    FUN_1095bef0(A, B, C, this, Flags);
}
