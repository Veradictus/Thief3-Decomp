// Game/Unsorted_10B5C500.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern void* DAT_10e83420[];

class Class_10E81130
{
public:
    Class_10E81130* FUN_10b46080();

    void** Unknown00;
    char Unknown04[0x160];
};

struct Struct_10B5C500
{
    int Unknown00;
    int Unknown04;
    int Unknown08;
};

class Class_10E83420 : public Class_10E81130
{
public:
    Class_10E83420* FUN_10b5c500();

    int Unknown164;
    int Unknown168;
    int Unknown16C;
    Struct_10B5C500 Unknown170[4];
    char Unknown1A0[0x34];
    int Unknown1D4;
    bool Unknown1D8;
    char Unknown1D9[0xF];
    int Unknown1E8;
    int Unknown1EC;
    int Unknown1F0;
    int Unknown1F4;
    int Unknown1F8;
    int Unknown1FC;
    int Unknown200;
    int Unknown204;
    int Unknown208;
    int Unknown20C;
    bool Unknown210;
    bool Unknown211;
    int Unknown214[3];
    char Unknown220[0xC];
    int Unknown22C;
    int Unknown230;
};

// FUNCTION: 0x10B5C500 ?FUN_10b5c500@Class_10E83420@@QAEPAV1@XZ
Class_10E83420* Class_10E83420::FUN_10b5c500()
{
    FUN_10b46080();
    Unknown00 = DAT_10e83420;
    Unknown164 = 0;
    Unknown168 = 0;
    Unknown16C = 0;
    for (int i = 0; i < 4; i++)
    {
        Unknown170[i].Unknown00 = 0;
        Unknown170[i].Unknown04 = 0;
        Unknown170[i].Unknown08 = 0;
    }
    Unknown1D4 = 0;
    Unknown1D8 = false;
    Unknown1E8 = 0;
    Unknown1EC = 0;
    Unknown1F0 = 0;
    Unknown1F4 = 0;
    Unknown1F8 = 0x40;
    Unknown1FC = 0;
    Unknown200 = 0;
    Unknown204 = 0;
    Unknown208 = 0;
    Unknown20C = 0;
    Unknown210 = false;
    Unknown211 = false;
    for (int j = 0; j < 3; j++)
        Unknown214[j] = 0;
    Unknown22C = 0;
    Unknown230 = 0;
    return this;
}
