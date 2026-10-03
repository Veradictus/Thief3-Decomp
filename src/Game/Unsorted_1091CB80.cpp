// Game/Unsorted_1091CB80.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_1091CB20
{
public:
    void FUN_1091be70();
    int FUN_1091cb80(unsigned int Index);

    int Count()
    {
        if (!Unknown0C)
            FUN_1091be70();
        return Unknown00;
    }

    int Unknown00;
    char Unknown04[4];
    int* Unknown08;
    bool Unknown0C;
};

// FUNCTION: 0x1091CB80 ?FUN_1091cb80@Class_1091CB20@@QAEHI@Z
int Class_1091CB20::FUN_1091cb80(unsigned int Index)
{
    if (Index >= Count())
        Index = Count() - 1;
    return Unknown08[Index];
}
