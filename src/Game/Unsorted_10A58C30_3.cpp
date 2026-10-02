// Game/Unsorted_10A58C30_3.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10BFBD70
{
public:
    void FUN_10bfbd70(int NewCount);

    int Count;
    int Unknown04;
    int* Data;
};

class Class_10A58FE0
{
public:
    void FUN_10a58fe0(int Index, int Value);

    char Unknown00[0x154];
    Class_10BFBD70 Unknown154;
};

// FUNCTION: 0x10A58FE0 ?FUN_10a58fe0@Class_10A58FE0@@QAEXHH@Z
void Class_10A58FE0::FUN_10a58fe0(int Index, int Value)
{
    if (Unknown154.Count < Index + 1)
        Unknown154.FUN_10bfbd70(Index + 1);
    Unknown154.Data[Index] = Value;
}
