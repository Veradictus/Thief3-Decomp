// Game/Unsorted_10924270.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_1094D740
{
public:
    void FUN_1094d740(int A, int B, int C);
};

struct Struct_10924370
{
    int Unknown00;
    int Unknown04;
    int Unknown08;
    char Unknown0C[0x14];
};

struct Struct_10924370_Rect
{
    int X;
    int Y;
    float W;
    float H;
};

class Class_10924370
{
public:
    void FUN_10924370(int Index);

    char Unknown00[0x14];
    int Unknown14;
    char Unknown18[0x18];
    Class_1094D740 Unknown30;
    char Unknown31[0x17];
    Struct_10924370 Unknown48[1];
};

// FUNCTION: 0x10924370 ?FUN_10924370@Class_10924370@@QAEXH@Z
void Class_10924370::FUN_10924370(int Index)
{
    Struct_10924370_Rect Rect = { 0, 0, 1.0f, 1.0f };
    if (Index != -1)
    {
        if (Unknown48[Index].Unknown00)
        {
            Rect.X = Unknown48[Index].Unknown04;
            Rect.Y = Unknown48[Index].Unknown08;
            Unknown30.FUN_1094d740(Unknown14, (int)&Rect, 0);
        }
    }
}
