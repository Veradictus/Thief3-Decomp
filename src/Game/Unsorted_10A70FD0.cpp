// Game/Unsorted_10A70FD0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern void* DAT_10e47850[];

extern float DAT_10eafbdc;

class Class_10AF4B90
{
public:
    Class_10AF4B90* FUN_10af4b90(int A, void* B);

    int Unknown00;
    int Unknown04;
    int Unknown08;
};

// A Class_10AF4B90 set up with (0x27, DAT_10e47850).
class Class_10A71030 : public Class_10AF4B90
{
public:
    Class_10A71030() { FUN_10af4b90(0x27, DAT_10e47850); }
    ~Class_10A71030();
};

// What FUN_10c070c0 fills in.
struct Class_10C070C0_Result
{
    int Unknown00;
    Class_10A71030 Unknown04;
    float Unknown10;
};

class Class_10C070C0
{
public:
    void FUN_10c070c0(int Id, Class_10C070C0_Result* Result);
};

class Class_10A67B70
{
public:
    virtual ~Class_10A67B70();
};

class Class_10E6B610 : public Class_10A67B70
{
public:
    Class_10E6B610(Class_10C070C0* A);

    float Unknown04;
    float Unknown08;
};

// FUNCTION: 0x10A710E0 ??0Class_10E6B610@@QAE@PAVClass_10C070C0@@@Z
Class_10E6B610::Class_10E6B610(Class_10C070C0* A)
{
    Class_10C070C0_Result Result;
    A->FUN_10c070c0(0x8038b, &Result);
    if (Result.Unknown10 <= DAT_10eafbdc)
        Unknown04 = Unknown08 = 1.0f;
    else
        Unknown04 = Unknown08 = Result.Unknown10;
}
