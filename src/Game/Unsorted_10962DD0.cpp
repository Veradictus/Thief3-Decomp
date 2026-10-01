// Game/Unsorted_10962DD0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern void* DAT_10e4c9e0[];

class Class_10E70A50
{
public:
    Class_10E70A50();

    void** Unknown00;
    char Unknown04[0x28];
};

class AActor : public Class_10E70A50
{
public:
    AActor* FUN_1098cf10();

    char Unknown2C[0x84];
    int UnknownB0;
    int UnknownB4;
    int UnknownB8;
};

class Class_10E4C9E0 : public AActor
{
public:
    Class_10E4C9E0* FUN_10962e50();
};

extern void* DAT_10e4cb58[];

class Class_10E4CB58 : public AActor
{
public:
    Class_10E4CB58* FUN_10962ef0();
};

class Class_10963740
{
public:
    Class_10963740* FUN_10963740(int A, int B, int C);

    int Unknown00;
    int Unknown04;
    int Unknown08;
};

// FUNCTION: 0x10962E50 ?FUN_10962e50@Class_10E4C9E0@@QAEPAV1@XZ
Class_10E4C9E0* Class_10E4C9E0::FUN_10962e50()
{
    FUN_1098cf10();
    Unknown00 = DAT_10e4c9e0;
    return this;
}

// FUNCTION: 0x10962EF0 ?FUN_10962ef0@Class_10E4CB58@@QAEPAV1@XZ
Class_10E4CB58* Class_10E4CB58::FUN_10962ef0()
{
    FUN_1098cf10();
    Unknown00 = DAT_10e4cb58;
    return this;
}

// FUNCTION: 0x10963740 ?FUN_10963740@Class_10963740@@QAEPAV1@HHH@Z
Class_10963740* Class_10963740::FUN_10963740(int A, int B, int C)
{
    Unknown00 = A;
    Unknown04 = B;
    Unknown08 = C;
    return this;
}
