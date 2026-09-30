// Game/Unsorted_10A84E60.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Struct_10A85890
{
    char Unknown00[0x14];
    int Unknown14;
    int Unknown18;
};

class Class_10A85890
{
public:
    void FUN_10a85110(Struct_10A85890* Ar);
    void FUN_10a852e0(Struct_10A85890* Ar);
    void FUN_10a85890(Struct_10A85890* Ar);
};

void FUN_10ad1dc0(void* Memory);

class Class_10A873D0
{
public:
    void FUN_10a86490(int A);
    void FUN_10a873d0();

    int Unknown00;
    int Unknown04;
    char Unknown08[4];
    int Unknown0C;
    char Unknown10[4];
    void* Unknown14;
};

// FUNCTION: 0x10A85890 ?FUN_10a85890@Class_10A85890@@QAEXPAUStruct_10A85890@@@Z
void Class_10A85890::FUN_10a85890(Struct_10A85890* Ar)
{
    if (Ar->Unknown14)
        FUN_10a852e0(Ar);
    else if (Ar->Unknown18)
        FUN_10a85110(Ar);
}

// FUNCTION: 0x10A873D0 ?FUN_10a873d0@Class_10A873D0@@QAEXXZ
void Class_10A873D0::FUN_10a873d0()
{
    FUN_10a86490(0x40);
    FUN_10ad1dc0(Unknown14);
    Unknown04 = 0;
    Unknown0C = 0;
    Unknown14 = 0;
    Unknown00 = 0;
}
