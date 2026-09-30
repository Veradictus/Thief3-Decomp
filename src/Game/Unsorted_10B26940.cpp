// Game/Unsorted_10B26940.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Struct_10F0328C
{
    float Unknown00;
    int Unknown04;
    int Unknown08;
    int Unknown0C;
};

extern Struct_10F0328C DAT_10f0328c[];

extern float DAT_10eafbdc;

class Class_10B27220
{
public:
    void FUN_10b27220(int Index);
    void FUN_10b270d0();

    char Unknown00[0x38];
    bool Unknown38;
};

// FUNCTION: 0x10B27220 ?FUN_10b27220@Class_10B27220@@QAEXH@Z
void Class_10B27220::FUN_10b27220(int Index)
{
    if (DAT_10f0328c[Index].Unknown00 > DAT_10eafbdc)
        Unknown38 = true;
    else
        FUN_10b270d0();
}
