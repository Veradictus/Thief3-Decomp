// Game/Unsorted_10B8ACC0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10B8AC90;

class Class_10D9B090
{
public:
    void FUN_10d9b090();
    void FUN_10d9b100();
};

Class_10D9B090* __stdcall FUN_10d9dcb0(Class_10B8AC90* Obj, int A);

struct Struct_10B8AC90
{
    char Unknown00[0x28];
    unsigned int Unknown28Bits0To4 : 5;
    unsigned int Unknown28Bits5To10 : 6;
    unsigned int Unknown28Bits11To16 : 6;
};

class Class_10B8AC90
{
public:
    void FUN_10b8ac90(int A);
    void FUN_10b8acc0(int A);

    char Unknown00[0x10];
    Struct_10B8AC90* Unknown10;
};

// FUNCTION: 0x10B8ACC0 ?FUN_10b8acc0@Class_10B8AC90@@QAEXH@Z
void Class_10B8AC90::FUN_10b8acc0(int A)
{
    if (A != Unknown10->Unknown28Bits5To10)
    {
        FUN_10d9dcb0(this, A)->FUN_10d9b100();
    }
}
