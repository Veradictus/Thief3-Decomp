// Game/Unsorted_10B31520.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10A55090
{
public:
    void FUN_10a55090(int A);
};

class Class_10B31520
{
public:
    void FUN_10b31520(float A);

    char Unknown00[0x134];
    Class_10A55090* Unknown134;
    char Unknown138[4];
    float Unknown13C;
    int Unknown140;
};

// FUNCTION: 0x10B31520 ?FUN_10b31520@Class_10B31520@@QAEXM@Z
void Class_10B31520::FUN_10b31520(float A)
{
    Unknown13C += A;
    if (Unknown13C >= 1.0f)
    {
        Unknown13C = 0.0f;
        if (Unknown134)
            Unknown134->FUN_10a55090(Unknown140);
    }
}
