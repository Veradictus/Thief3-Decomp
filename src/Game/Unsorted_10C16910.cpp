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

struct Struct_10C17BC0
{
    char Unknown00[0xC];
};

void FUN_10c17bc0(void* A, Struct_10C17BC0* B);

class Class_10E98CA4
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void FUN_10c17c10(void* A);

    char Unknown04[0xC];
    Struct_10C17BC0 Unknown10;
    Struct_10C17BC0 Unknown1C;
    Struct_10C17BC0 Unknown28;
    char Unknown34[0x70];
    void* UnknownA4;
};

// FUNCTION: 0x10C17C10 ?FUN_10c17c10@Class_10E98CA4@@UAEXPAX@Z
void Class_10E98CA4::FUN_10c17c10(void* A)
{
    FUN_10c17bc0(A, &Unknown10);
    FUN_10c17bc0(A, &Unknown1C);
    FUN_10c17bc0(A, &Unknown28);
    if (UnknownA4 == A)
        UnknownA4 = 0;
}

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
