// Game/Unsorted_10A66EC0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10A66FE0_Field0C0
{
public:
    char Unknown00[0xC8];
    int Unknown0C8;
};

class Class_10A66FE0
{
public:
    void FUN_10a66fe0(int A);

    char Unknown00[0x34];
    int Unknown34;
    char Unknown38[0x88];
    Class_10A66FE0_Field0C0* Unknown0C0;
    char Unknown0C4[0x74];
    int Unknown138;
};

// FUNCTION: 0x10A66FE0 ?FUN_10a66fe0@Class_10A66FE0@@QAEXH@Z
void Class_10A66FE0::FUN_10a66fe0(int A)
{
    if (!Unknown0C0 || (Unknown0C0->Unknown0C8 & 1))
        Unknown138 = Unknown34;
}
