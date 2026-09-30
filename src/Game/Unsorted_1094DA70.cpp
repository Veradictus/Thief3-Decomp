// Game/Unsorted_1094DA70.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_1094DF60
{
public:
    void FUN_1094df60(int A);

    char Unknown00[0x10C];
    int Unknown10C;
    int Unknown110;
};

// FUNCTION: 0x1094DF60 ?FUN_1094df60@Class_1094DF60@@QAEXH@Z
void Class_1094DF60::FUN_1094df60(int A)
{
    Unknown110 = A;
    if (Unknown110 >= Unknown10C)
        Unknown110 = Unknown10C - 1;
    if (Unknown110 < 0)
        Unknown110 = 0;
}
