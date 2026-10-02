// Game/Unsorted_10A58C30_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10BFBD70
{
public:
    void FUN_10a58cb0(const Class_10BFBD70& Other);
    void FUN_10bfbd70(int NewCount);

    int Count;
    int Unknown04;
    int* Data;
};

// FUNCTION: 0x10A58CB0 ?FUN_10a58cb0@Class_10BFBD70@@QAEXABV1@@Z
void Class_10BFBD70::FUN_10a58cb0(const Class_10BFBD70& Other)
{
    FUN_10bfbd70(Other.Count);
    for (int i = 0; i < Count; i++)
        Data[i] = Other.Data[i];
}
