// Game/Unsorted_1094E150.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10953590;

class Class_10939570
{
public:
    void FUN_1093bce0(Class_10953590* Param);
};

extern Class_10939570* DAT_10f323fc;

struct Struct_1094E150_Item
{
    Class_10953590* Unknown00;
};

class Class_1094E150
{
public:
    void FUN_1094e150();

    char Unknown00[0xF0];
    int Unknown0F0;
    char Unknown0F4[8];
    Struct_1094E150_Item** Unknown0FC;
};

// FUNCTION: 0x1094E150 ?FUN_1094e150@Class_1094E150@@QAEXXZ
void Class_1094E150::FUN_1094e150()
{
    for (int i = 0; i < Unknown0F0; i++)
    {
        DAT_10f323fc->FUN_1093bce0(Unknown0FC[i]->Unknown00);
        if (Unknown0FC[i])
            delete Unknown0FC[i];
        Unknown0FC[i] = 0;
    }
}
