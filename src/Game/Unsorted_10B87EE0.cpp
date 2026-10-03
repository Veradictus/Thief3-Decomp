// Game/Unsorted_10B87EE0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Struct_10B87F00
{
    char Unknown00[0x74];
};

class Class_10ACCFB0
{
public:
    void FUN_10acc790(int NewCount);
    void FUN_10b87f00(const Class_10ACCFB0& Other);

    int Count;
    int Unknown04;
    Struct_10B87F00* Data;
};

// FUNCTION: 0x10B87F00 ?FUN_10b87f00@Class_10ACCFB0@@QAEXABV1@@Z
void Class_10ACCFB0::FUN_10b87f00(const Class_10ACCFB0& Other)
{
    FUN_10acc790(Other.Count);
    for (int i = 0; i < Count; i++)
        Data[i] = Other.Data[i];
}
