// Game/Unsorted_10BFB8D0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

float appFrand();

double FUN_10c00480();

struct Range_10BFB8D0
{
    float Unknown00;
    float Unknown04;
    float Unknown08;
};

class Class_10bfb8d0
{
public:
    void FUN_10bfb8d0(int A);

    char Unknown00[4];
    Range_10BFB8D0 Unknown04[10];
};

// FUNCTION: 0x10BFB8D0 ?FUN_10bfb8d0@Class_10bfb8d0@@QAEXH@Z
void Class_10bfb8d0::FUN_10bfb8d0(int A)
{
    Unknown04[A].Unknown08 = Unknown04[A].Unknown00 + appFrand() * (Unknown04[A].Unknown04 - Unknown04[A].Unknown00) + FUN_10c00480();
}
