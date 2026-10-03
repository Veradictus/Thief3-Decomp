// Game/Unsorted_10A58C70.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10BFBD70
{
public:
    void FUN_10a58c70(const Class_10BFBD70& Other);
    void FUN_10bfbd70(int NewCount);
    void FUN_109dff50(int Index);

    int FindIndex(int Item)
    {
        for (int i = 0; i < Count; i++)
        {
            if (Data[i] == Item)
                return i;
        }
        return -1;
    }

    int Count;
    int Unknown04;
    int* Data;
};

// FUNCTION: 0x10A58C70 ?FUN_10a58c70@Class_10BFBD70@@QAEXABV1@@Z
void Class_10BFBD70::FUN_10a58c70(const Class_10BFBD70& Other)
{
    int OldCount = Count;
    FUN_10bfbd70(Other.Count + OldCount);
    for (int i = 0; i < Other.Count; i++)
        Data[OldCount + i] = Other.Data[i];
}
