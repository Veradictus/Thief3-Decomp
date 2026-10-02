// Game/Unsorted_10B39790.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10B47720
{
public:
    void FUN_10b47720(int A);
};

class Class_10B39870
{
public:
    int FUN_10b39870(int A);

    char Unknown00[0xC];
    Class_10B47720* Unknown0C;
};

struct Static_10B3A410
{
    Static_10B3A410() : Unknown00(0), Unknown04(0), Unknown08(0), Unknown10(0), Unknown14(0), Unknown18(0) {}
    ~Static_10B3A410();

    int Unknown00;
    int Unknown04;
    int Unknown08;
    int Unknown0C;
    int Unknown10;
    int Unknown14;
    int Unknown18;
};

class Class_10B47180
{
public:
    void FUN_10b47180(int A, int B, int C, int D);
};

class Class_10B3A460
{
public:
    Class_10B3A460* FUN_10b3a460(int A);

    char Unknown00[0x1C];
    int Unknown1C;
};

Class_10B3A460* FUN_10b3abf0();

class Class_10B397D0
{
public:
    void FUN_10b397d0(int A, int B, int C, int D);

    char Unknown00[0xC];
    Class_10B47180* Unknown0C[1];
};

// FUNCTION: 0x10B397D0 ?FUN_10b397d0@Class_10B397D0@@QAEXHHHH@Z
void Class_10B397D0::FUN_10b397d0(int A, int B, int C, int D)
{
    int Index = FUN_10b3abf0()->FUN_10b3a460(A)->Unknown1C;
    Unknown0C[Index]->FUN_10b47180(A, B, C, D);
}

// FUNCTION: 0x10B39870 ?FUN_10b39870@Class_10B39870@@QAEHH@Z
int Class_10B39870::FUN_10b39870(int A)
{
    Unknown0C->FUN_10b47720(A);
    return A;
}

// FUNCTION: 0x10B3A410 ?FUN_10b3a410@@YAPAUStatic_10B3A410@@XZ
Static_10B3A410* FUN_10b3a410()
{
    static Static_10B3A410 Instance;
    return &Instance;
}
