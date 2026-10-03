// Game/InnerClassAE0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10924E80
{
public:
    void FUN_10925db0(int Item);
};

extern Class_10924E80* DAT_10f2c734;

class Class_10BFBD70
{
public:
    int Unknown00;
    int Unknown04;
    int* Unknown08;
};

class InnerClassAE0_Unknown00
{
public:
    char Unknown00[0xC];
    Class_10BFBD70 Unknown0C;
};

class InnerClassAE0
{
public:
    void FUN_10c5fb50();

    InnerClassAE0_Unknown00* Unknown00;
};

// FUNCTION: 0x10C5FB50 ?FUN_10c5fb50@InnerClassAE0@@QAEXXZ
void InnerClassAE0::FUN_10c5fb50()
{
    InnerClassAE0_Unknown00* Owner = Unknown00;
    if (DAT_10f2c734)
    {
        for (int i = 0; i < Owner->Unknown0C.Unknown00; i++)
            DAT_10f2c734->FUN_10925db0(Owner->Unknown0C.Unknown08[i]);
    }
}
