// Game/Unsorted_10C04810_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10C04810
{
public:
    char Unknown00[0x24];
    int Unknown24[1];

    int FUN_10c04810(int index);
};

class Class_10C04820
{
public:
    char Unknown00[0x1F];
    unsigned char Unknown1F[1];

    unsigned char FUN_10c04820(int index);
};

class Class_10BFBD70
{
public:
    void FUN_10bfbd70(int NewCount);

    int Unknown00;
    int Unknown04;
    int* Unknown08;
};

class Class_10C04D90
{
public:
    bool FUN_10c04d90(int Value);

    char Unknown00[0x20];
    Class_10BFBD70 Unknown20;
};

extern float DAT_10e97b5c;

// FUNCTION: 0x10C04810 ?FUN_10c04810@Class_10C04810@@QAEHH@Z
int Class_10C04810::FUN_10c04810(int index)
{
    return Unknown24[index];
}

// FUNCTION: 0x10C04820 ?FUN_10c04820@Class_10C04820@@QAEEH@Z
unsigned char Class_10C04820::FUN_10c04820(int index)
{
    return Unknown1F[index];
}

// FUNCTION: 0x10C04D90 ?FUN_10c04d90@Class_10C04D90@@QAE_NH@Z
bool Class_10C04D90::FUN_10c04d90(int Value)
{
    Class_10BFBD70* Array = &Unknown20;
    int Index = Array->Unknown00;
    Array->FUN_10bfbd70(Index + 1);
    Array->Unknown08[Index] = Value;
    return true;
}

// FUNCTION: 0x10C064C0 ?FUN_10c064c0@@YAMXZ
float FUN_10c064c0()
{
    return DAT_10e97b5c;
}
