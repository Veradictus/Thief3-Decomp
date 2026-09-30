// Game/Unsorted_109E3860.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_109E38A0 {
public:
    void FUN_109e38a0(unsigned char p1);
    char Unknown00[0xce];
    unsigned char FieldCE;
};

class Class_109E38C0 {
public:
    void FUN_109e38c0(int p1);
    char Unknown00[0xb0];
    int FieldB0;
};

class Class_109E38D0
{
public:
    char Unknown00[0xb0];
    void* FieldB0;
    void* FUN_109e38d0();
};

// FUNCTION: 0x109E38A0 ?FUN_109e38a0@Class_109E38A0@@QAEXE@Z
void Class_109E38A0::FUN_109e38a0(unsigned char p1)
{
    FieldCE = p1;
}

// FUNCTION: 0x109E38B0 ?FUN_109e38b0@@YGXHH@Z
void __stdcall FUN_109e38b0(int p1, int p2)
{
}

// FUNCTION: 0x109E38C0 ?FUN_109e38c0@Class_109E38C0@@QAEXH@Z
void Class_109E38C0::FUN_109e38c0(int p1)
{
    FieldB0 = p1;
}

// FUNCTION: 0x109E38D0 ?FUN_109e38d0@Class_109E38D0@@QAEPAXXZ
void* Class_109E38D0::FUN_109e38d0()
{
    return FieldB0;
}
