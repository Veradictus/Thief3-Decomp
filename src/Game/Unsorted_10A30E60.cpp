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

class Class_10A311E0
{
public:
    void FUN_10a30f20();

    void Destroy()
    {
        FUN_10a30f20();
        ::operator delete(this);
    }
};

extern Class_10A311E0* DAT_10f39f3c;

// FUNCTION: 0x10A311E0 ?FUN_10a311e0@@YAXXZ
void FUN_10a311e0()
{
    if (DAT_10f39f3c)
    {
        DAT_10f39f3c->Destroy();
        DAT_10f39f3c = 0;
    }
}

// FUNCTION: 0x10A32910 ?FUN_10a32910@Class_10A32000@@QAEHPAD@Z
int Class_10A32000::FUN_10a32910(char* Value)
{
    int Index = Unknown00;
    FUN_10a32000(Index + 1);
    Unknown08[Index] = *Value;
    return Index;
}
