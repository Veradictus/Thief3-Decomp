// Game/Unsorted_10955B20.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_1095AFD0
{
public:
    ~Class_1095AFD0();
};

void FUN_1092bdb0(void* P);

class Class_10955C30
{
public:
    void FUN_10955c30();
    void FUN_10956270();

    const char* Unknown00;
    char Unknown04[4];
    int Unknown08;
    char Unknown0C[0xC];
    void* Unknown18;
    Class_1095AFD0* Unknown1C;
};

extern const char DAT_10e47660[];

int FUN_1095af30(int A);

void* FUN_1092cac0(const char* Name, int A, int B, int C, int D, int E);

// FUNCTION: 0x10955C30 ?FUN_10955c30@Class_10955C30@@QAEXXZ
void Class_10955C30::FUN_10955c30()
{
    if (Unknown1C)
        delete Unknown1C;
    else if (Unknown18)
        FUN_1092bdb0(Unknown18);
    Unknown1C = 0;
    Unknown18 = 0;
}

// FUNCTION: 0x10956270 ?FUN_10956270@Class_10955C30@@QAEXXZ
void Class_10955C30::FUN_10956270()
{
    const char* Name = DAT_10e47660;
    if (Unknown00)
        Name = Unknown00;
    Unknown18 = FUN_1092cac0(Name, Unknown08, FUN_1095af30(Unknown08), 0, 0, 0);
}
