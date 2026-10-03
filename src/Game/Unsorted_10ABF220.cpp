// Game/Unsorted_10ABF220.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10ABFB00_Member
{
public:
    virtual void Virtual0(float* A, float* B, int C);
};

class Class_10ABFB00
{
public:
    void FUN_10abf660(int A);
    void FUN_10abf7c0(int A);
    void FUN_10abfb00(int A, bool State);

    bool Unknown00;
    char Unknown01[0xB];
    float Unknown0C;
    char Unknown10[0x10];
    Class_10ABFB00_Member Unknown20;
};

// FUNCTION: 0x10ABFB00 ?FUN_10abfb00@Class_10ABFB00@@QAEXH_N@Z
void Class_10ABFB00::FUN_10abfb00(int A, bool State)
{
    float Level = State ? 1.0f : 0.0f;
    float* Value = &Unknown0C;
    *Value = Level;
    Unknown20.Virtual0(Value, Value, 0);
    Unknown00 = State;
    FUN_10abf660(A);
    FUN_10abf7c0(A);
}
