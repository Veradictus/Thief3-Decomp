// Game/Unsorted_10AC9350.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_1098E330
{
public:
    void FUN_1098e330(int Id, int* Out);
};

// FUNCTION: 0x10ACC480 ?FUN_10acc480@@YGHHHH@Z
int __stdcall FUN_10acc480(int p1, int p2, int p3)
{
    return 2;
}

// FUNCTION: 0x10ACC4A0 ?FUN_10acc4a0@@YGMPAVClass_1098E330@@HH@Z
float __stdcall FUN_10acc4a0(Class_1098E330* Obj, int, int)
{
    float Value = -1.0f;
    Obj->FUN_1098e330(0x10058a, (int*)&Value);
    return Value;
}
