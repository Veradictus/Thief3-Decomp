// Game/Unsorted_10A30E60.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10A32000
{
public:
    void FUN_10a32000(int Count);
    int FUN_10a32910(char* Value);

    int Unknown00;
    int Unknown04;
    char* Unknown08;
};

// FUNCTION: 0x10A32910 ?FUN_10a32910@Class_10A32000@@QAEHPAD@Z
int Class_10A32000::FUN_10a32910(char* Value)
{
    int Index = Unknown00;
    FUN_10a32000(Index + 1);
    Unknown08[Index] = *Value;
    return Index;
}
