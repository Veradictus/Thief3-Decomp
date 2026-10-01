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
