// Game/Unsorted_10AC1530.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_1098E330
{
public:
    void FUN_1098e330(int Id, int* Out);
};

struct Struct_10AA3520
{
    char Unknown00[8];
    Class_1098E330* Unknown08;
};

extern Struct_10AA3520* DAT_10f35dec;

// FUNCTION: 0x10AC1610 ?FUN_10ac1610@@YAMXZ
float FUN_10ac1610()
{
    float Value = 75.0f;
    if (DAT_10f35dec->Unknown08)
        DAT_10f35dec->Unknown08->FUN_1098e330(0x100534, (int*)&Value);
    return Value;
}
