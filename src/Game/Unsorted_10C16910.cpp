// Game/Unsorted_10C16910.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern int DAT_10ff708c;

class Class_10BA9EE0
{
public:
    int FUN_10ba9ee0();
};

struct Struct_10C184F0
{
    int Unknown00;
    int Unknown04;
    int Unknown08;
};

class Class_10C184F0
{
public:
    void FUN_10c184f0();
    float FUN_10c18430(int A, Struct_10C184F0* B, int C, bool D);

    char Unknown00[4];
    Class_10BA9EE0* Unknown04;
};

class Class_10C19FD0
{
public:
    ~Class_10C19FD0();

    int Unknown00;
};

extern Class_10C19FD0* DAT_10ff7088;

// FUNCTION: 0x10C184F0 ?FUN_10c184f0@Class_10C184F0@@QAEXXZ
void Class_10C184F0::FUN_10c184f0()
{
    Struct_10C184F0 Result;
    FUN_10c18430(Unknown04->FUN_10ba9ee0(), &Result, 1, false);
}

// FUNCTION: 0x10C1A090 ?FUN_10c1a090@@YAXXZ
void FUN_10c1a090()
{
    --DAT_10ff7088->Unknown00;
    if (DAT_10ff7088->Unknown00 == 0)
    {
        delete DAT_10ff7088;
        DAT_10ff7088 = 0;
    }
}

// FUNCTION: 0x10C1A130 ?FUN_10c1a130@@YAXXZ
void FUN_10c1a130()
{
    --*(int*)DAT_10ff708c;
    if (*(int*)DAT_10ff708c == 0)
    {
        ::operator delete((void*)DAT_10ff708c);
        DAT_10ff708c = 0;
    }
}
