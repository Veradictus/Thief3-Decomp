// Game/Unsorted_109E49A0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Struct_109E4FB0_Item
{
};

class Class_109E4FB0
{
public:
    void FUN_109e4fb0();

    char Unknown00[0x1E8];
    int Unknown1E8;
    int Unknown1EC;
    Struct_109E4FB0_Item** Unknown1F0;
};

// FUNCTION: 0x109E4FB0 ?FUN_109e4fb0@Class_109E4FB0@@QAEXXZ
void Class_109E4FB0::FUN_109e4fb0()
{
    for (int i = 0; i < Unknown1E8; i++)
    {
        if (Unknown1F0[i])
        {
            delete Unknown1F0[i];
            Unknown1F0[i] = 0;
        }
    }
}
