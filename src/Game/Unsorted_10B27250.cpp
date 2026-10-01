// Game/Unsorted_10B27250.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10A556F0
{
public:
    void FUN_10a556f0(int p1);
};

class Class_10B274B0
{
public:
    void FUN_10b274b0(int p1);

    char Unknown00[0x1D0];
    Class_10A556F0* Unknown1D0;
};

class Class_10B274D0
{
public:
    void FUN_10b274d0(int p1);

    char Unknown00[0x1D4];
    Class_10A556F0* Unknown1D4;
};

// FUNCTION: 0x10B274B0 ?FUN_10b274b0@Class_10B274B0@@QAEXH@Z
void Class_10B274B0::FUN_10b274b0(int p1)
{
    if (Unknown1D0)
        Unknown1D0->FUN_10a556f0(p1);
}

// FUNCTION: 0x10B274D0 ?FUN_10b274d0@Class_10B274D0@@QAEXH@Z
void Class_10B274D0::FUN_10b274d0(int p1)
{
    if (Unknown1D4)
        Unknown1D4->FUN_10a556f0(p1);
}
