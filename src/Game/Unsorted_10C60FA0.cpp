// Game/Unsorted_10C60FA0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

double FUN_10d219e0(double X);

struct Struct_10C60FA0
{
    char Unknown00[0xC];
    unsigned short Unknown0C;
    unsigned short Unknown0E;
};

class Class_10C60FA0
{
public:
    int FUN_10c60fa0(int A);

    char Unknown00[0x1C];
    Struct_10C60FA0* Unknown1C;
};

// FUNCTION: 0x10C60FA0 ?FUN_10c60fa0@Class_10C60FA0@@QAEHH@Z
int Class_10C60FA0::FUN_10c60fa0(int A)
{
    int X = Unknown1C->Unknown0E >> 3;
    int Y = Unknown1C->Unknown0C;
    int Size = X > Y ? X : Y;
    if (Size == 0)
        Size = 1;
    return (int)(FUN_10d219e0((float)A / Size + 0.5) * Size);
}
