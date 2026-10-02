// Game/Unsorted_10AC87D0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10E67938
{
public:
    Class_10E67938();

    virtual void FUN_10a4c470(int Type, int A, int B, int C);
};

struct Struct_10AC90F0
{
    int Unknown00;
    int Unknown04;
    int Unknown08;

    Struct_10AC90F0() : Unknown00(0), Unknown04(0), Unknown08(0) {}
};

class Class_10E6FCBC : public Class_10E67938
{
public:
    Class_10E6FCBC();

    Struct_10AC90F0 Unknown04;
};

void* FUN_10ac89c0();

void FUN_10ac87f0(void* Obj, int A, int B);

// FUNCTION: 0x10AC8BE0 ?FUN_10ac8be0@@YGXHH@Z
void __stdcall FUN_10ac8be0(int A, int B)
{
    void* Obj = FUN_10ac89c0();
    if (Obj)
        FUN_10ac87f0(Obj, A, B);
}

// FUNCTION: 0x10AC90F0 ??0Class_10E6FCBC@@QAE@XZ
Class_10E6FCBC::Class_10E6FCBC()
{
}
