// Game/Unsorted_10939380.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_109394C0 {
public:
    char Unknown00[8];
    int Unknown08;
    int Unknown0c;
    int Unknown10;
    Class_109394C0* FUN_109394c0();
};

class Class_1090A780
{
public:
    Class_1090A780(const Class_1090A780& Other);
    ~Class_1090A780();

    char* Unknown00;
};

struct Struct_1093BCB0
{
    int Unknown00;
    Class_1090A780 Unknown04;
    char Unknown08[0x4C];
    int Unknown54;
};

class Class_1093bcb0
{
public:
    bool FUN_1093b260(const Class_1090A780& Name, Struct_1093BCB0** Out);
    int FUN_1093bcb0(Struct_1093BCB0* Info);
};


class Class_1093C750
{
public:
    void FUN_1093b450(int A);
    void FUN_1093c750();

    int Unknown00;
    int Unknown04;
    int Unknown08;
    int Unknown0C;
    int Unknown10;
    void* Unknown14;
};

// FUNCTION: 0x109394C0 ?FUN_109394c0@Class_109394C0@@QAEPAV1@XZ
Class_109394C0* Class_109394C0::FUN_109394c0()
{
    Unknown08 = 0;
    Unknown0c = 0;
    Unknown10 = 0;
    return this;
}

// FUNCTION: 0x1093BCB0 ?FUN_1093bcb0@Class_1093bcb0@@QAEHPAUStruct_1093BCB0@@@Z
int Class_1093bcb0::FUN_1093bcb0(Struct_1093BCB0* Info)
{
    if (FUN_1093b260(Info->Unknown04, &Info))
        return Info->Unknown54;
    return -1;
}

// FUNCTION: 0x1093C750 ?FUN_1093c750@Class_1093C750@@QAEXXZ
void Class_1093C750::FUN_1093c750()
{
    FUN_1093b450(0x40);
    ::operator delete(Unknown14);
    Unknown04 = 0;
    Unknown0C = 0;
    Unknown14 = 0;
    Unknown00 = 0;
}
