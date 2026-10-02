// Game/Unsorted_10952740_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern int DAT_10f3419c;

extern int DAT_10f341a0;

bool FUN_10952740();

struct Struct_109528B0
{
    char Unknown00[0x30];
    int Unknown30;
};

class Class_109528B0
{
public:
    void FUN_10952870(int Index);

    char Unknown00[0xA8];
    Struct_109528B0* UnknownA8;
};

// FUNCTION: 0x10952870 ?FUN_10952870@Class_109528B0@@QAEXH@Z
void Class_109528B0::FUN_10952870(int Index)
{
    if ((DAT_10f3419c == 0 || DAT_10f341a0 == 0) && !FUN_10952740())
        return;
    UnknownA8->Unknown30 = (&DAT_10f3419c)[Index];
}
