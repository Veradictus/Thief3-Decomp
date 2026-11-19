// Game/LinkedMotionDisable.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10B47090
{
public:
    void FUN_10b47090();
};

// Handler table+0C matches the accepted neighboring10B398B0 indexed wrapper.
class Class_10B398C0
{
public:
    void FUN_10b398c0(int Index);
    char Pad00[0xC];
    Class_10B47090* Unknown0C[8];
};

// FUNCTION: 0x10B398C0 ?FUN_10b398c0@Class_10B398C0@@QAEXH@Z
void Class_10B398C0::FUN_10b398c0(int Index)
{
    Unknown0C[Index]->FUN_10b47090();
}
