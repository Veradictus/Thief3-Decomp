// Game/Unsorted_10BAD9B0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10A68D20;

extern const char DAT_10e47660[];

void FUN_10a68d50(Class_10A68D20* Owner, int A, int B, int C, int D);

class Class_10E8DBA4
{
public:
    virtual void FUN_10baeb30(Class_10A68D20* Owner);

    char Unknown04[4];
    int Unknown08;
    char Unknown0C[8];
    int Unknown14;
    const char* Unknown18;
};

void FUN_10a68d20(Class_10A68D20* Owner, int A, int B, int C);

class Class_10E8D7B8
{
public:
    virtual void FUN_10bad9b0(Class_10A68D20* Owner);

    char Unknown04[4];
    int Unknown08;
    char Unknown0C[8];
    int Unknown14;
    int Unknown18;
};

extern const char DAT_10e8d94c[];

class Class_109081E0
{
public:
    Class_109081E0(const char* In);
    ~Class_109081E0();

    char* Unknown00;
};

// FUNCTION: 0x10BAD9B0 ?FUN_10bad9b0@Class_10E8D7B8@@UAEXPAVClass_10A68D20@@@Z
void Class_10E8D7B8::FUN_10bad9b0(Class_10A68D20* Owner)
{
    FUN_10a68d20(Owner, (int)&Unknown08, (int)&Unknown14, Unknown18);
}

// FUNCTION: 0x10BAEB10 ?FUN_10baeb10@@YA?AVClass_109081E0@@XZ
Class_109081E0 FUN_10baeb10()
{
    return Class_109081E0(DAT_10e8d94c);
}

// FUNCTION: 0x10BAEB30 ?FUN_10baeb30@Class_10E8DBA4@@UAEXPAVClass_10A68D20@@@Z
void Class_10E8DBA4::FUN_10baeb30(Class_10A68D20* Owner)
{
    const char* Name = Unknown18;
    if (!Name)
        Name = DAT_10e47660;
    FUN_10a68d50(Owner, (int)Name, (int)&Unknown08, (int)&Unknown14, 0);
}
