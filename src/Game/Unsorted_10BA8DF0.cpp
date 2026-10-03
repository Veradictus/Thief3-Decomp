// Game/Unsorted_10BA8DF0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10C05E30
{
public:
    Class_10C05E30(int A, int B);

    char Unknown00[0x24];
};

void FUN_10c05f10(const Class_10C05E30* A, const Class_10C05E30* B, int C, int D);

// FUNCTION: 0x10BA8DF0 ?FUN_10ba8df0@@YAXHHHHH@Z
void FUN_10ba8df0(int A, int B, int C, int D, int E)
{
    Class_10C05E30 First(A, B);
    Class_10C05E30 Second(C, D);
    FUN_10c05f10(&First, &Second, E, 1);
}
