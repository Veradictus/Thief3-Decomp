// Game/Unsorted_1093EDB0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Struct_10940180
{
    char Unknown00[0x64];
    int Unknown64;
};

class Class_10940180
{
public:
    void FUN_10940180(Struct_10940180* P);
    void FUN_1093fed0(Struct_10940180* P);
    void FUN_1093ff60(Struct_10940180* P);
};

class Class_109418E0
{
public:
    void FUN_109418e0();

    char Unknown00[6];
    char Unknown06;
    char Unknown07[0x31];
    int Unknown38;
};

class Class_10941C40
{
public:
    void FUN_10941b10(int A);
    void FUN_10941c40();

    char Unknown00[0x10];
    int Unknown10;
    char Unknown14[8];
    Class_109418E0* Unknown1C;
};

class Class_10951730
{
public:
    void FUN_10951730(int p1);
};

class Class_10e4a668
{
public:
    virtual void Virtual0();
    virtual void FUN_10942030(int p1);

    char Unknown04[0xAC];
    Class_10951730* UnknownB0;
};

// FUNCTION: 0x10940180 ?FUN_10940180@Class_10940180@@QAEXPAUStruct_10940180@@@Z
void Class_10940180::FUN_10940180(Struct_10940180* P)
{
    switch (P->Unknown64)
    {
    case 4:
        FUN_1093fed0(P);
        break;
    case 5:
        FUN_1093ff60(P);
        break;
    }
}

// FUNCTION: 0x10941C40 ?FUN_10941c40@Class_10941C40@@QAEXXZ
void Class_10941C40::FUN_10941c40()
{
    if (Unknown1C == 0)
        FUN_10941b10(0);
    int Value = Unknown10;
    Class_109418E0* Item = Unknown1C;
    Item->Unknown06 = 0;
    Item->Unknown38 = Value;
    Item->FUN_109418e0();
}

// FUNCTION: 0x10942030 ?FUN_10942030@Class_10e4a668@@UAEXH@Z
void Class_10e4a668::FUN_10942030(int p1)
{
    if (UnknownB0)
        UnknownB0->FUN_10951730(p1);
}
