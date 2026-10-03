// Game/Unsorted_10B31B30.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Struct_10AA3520_Unknown08
{
    char Unknown00[0x440];
    int Unknown440;
    int Unknown444;
    int Unknown448;
};

struct Struct_10AA3520
{
    char Unknown00[0x8];
    Struct_10AA3520_Unknown08* Unknown08;
};

extern Struct_10AA3520* DAT_10f35dec;

class Class_10B31B30
{
public:
    bool FUN_10b31b30();

    char Unknown00[0x30];
    char Unknown30;
    char Unknown31;
    char Unknown32;
};

// FUNCTION: 0x10B31B30 ?FUN_10b31b30@Class_10B31B30@@QAE_NXZ
bool Class_10B31B30::FUN_10b31b30()
{
    Struct_10AA3520_Unknown08* Owner = DAT_10f35dec->Unknown08;
    if (Owner->Unknown440 && Owner->Unknown448 && Owner->Unknown444)
        return !Unknown30 && Unknown32;
    return false;
}
