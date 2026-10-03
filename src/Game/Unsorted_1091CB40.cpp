// Game/Unsorted_1091CB40.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10919C40
{
public:
    float FUN_10919c40(int A);

    char Unknown00[0x14];
    float Unknown14;
};

class Class_1091CB20
{
public:
    int FUN_1091cb40();
    void FUN_1091be70();

    int Unknown00;
    char Unknown04[8];
    bool Unknown0C;
    char Unknown0D[0xB];
    float Unknown18;
    int Unknown1C;
    Class_10919C40* Unknown20;
};

// FUNCTION: 0x1091CB40 ?FUN_1091cb40@Class_1091CB20@@QAEHXZ
int Class_1091CB20::FUN_1091cb40()
{
    if (!Unknown0C)
        FUN_1091be70();
    int Index = Unknown1C;
    Class_10919C40* Item = Unknown20;
    int Value = (int)(Item->FUN_10919c40(Index) * Item->Unknown14);
    return (int)(Unknown18 / Value);
}
