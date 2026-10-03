// Game/Unsorted_10B597B0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Struct_10B597B0
{
    int Unknown00;
    int Unknown04;
};

class Class_10B59770
{
public:
    void FUN_10abc210(int NewCount);
    void FUN_10b597b0(const Class_10B59770& Other);

    int Count;
    int Unknown04;
    Struct_10B597B0* Data;
};

// FUNCTION: 0x10B597B0 ?FUN_10b597b0@Class_10B59770@@QAEXABV1@@Z
void Class_10B59770::FUN_10b597b0(const Class_10B59770& Other)
{
    FUN_10abc210(Other.Count);
    for (int i = 0; i < Count; i++)
        Data[i] = Other.Data[i];
}
