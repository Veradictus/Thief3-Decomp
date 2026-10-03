// Game/Unsorted_1091F380.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10924100_Unknown44
{
public:
    virtual void Virtual0(int A);

    char Unknown04[0x58];
    int Unknown5C;
};

class Class_10924100
{
public:
    void FUN_1091f6a0();
    bool FUN_1091f6e0(Class_10924100_Unknown44* Item);

    char Unknown00[0x3C];
    int Unknown3C;
    char Unknown40[4];
    Class_10924100_Unknown44** Unknown44;
};

// FUNCTION: 0x1091F6A0 ?FUN_1091f6a0@Class_10924100@@QAEXXZ
void Class_10924100::FUN_1091f6a0()
{
    for (int i = 0; i < Unknown3C; i++)
    {
        Unknown44[i]->Unknown5C |= 1;
        Unknown44[i]->Virtual0(0);
    }
}

// FUNCTION: 0x1091F6E0 ?FUN_1091f6e0@Class_10924100@@QAE_NPAVClass_10924100_Unknown44@@@Z
bool Class_10924100::FUN_1091f6e0(Class_10924100_Unknown44* Item)
{
    if (Item)
    {
        for (int i = 0; i < Unknown3C; i++)
        {
            if (Unknown44[i] == Item)
                return true;
        }
    }
    return false;
}
