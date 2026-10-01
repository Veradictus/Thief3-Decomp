// Game/Unsorted_10962700.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern void* DAT_10e4baf0[];

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

class Class_10E4BAF0 : public AActor
{
public:
    Class_10E4BAF0* FUN_10962860();
};

extern void* DAT_10e4bc68[];

class Class_10E4BC68 : public AActor
{
public:
    Class_10E4BC68* FUN_10962900();
};

class AAIPawnController
{
public:
    AAIPawnController();

    virtual void Virtual0();
};

class Class_10E4C3C0 : public AAIPawnController
{
public:
    Class_10E4C3C0();
};

// FUNCTION: 0x10962860 ?FUN_10962860@Class_10E4BAF0@@QAEPAV1@XZ
Class_10E4BAF0* Class_10E4BAF0::FUN_10962860()
{
    FUN_1098cf10();
    Unknown00 = DAT_10e4baf0;
    return this;
}

// FUNCTION: 0x10962900 ?FUN_10962900@Class_10E4BC68@@QAEPAV1@XZ
Class_10E4BC68* Class_10E4BC68::FUN_10962900()
{
    FUN_1098cf10();
    Unknown00 = DAT_10e4bc68;
    return this;
}

// FUNCTION: 0x10962BD0 ??0Class_10E4C3C0@@QAE@XZ
Class_10E4C3C0::Class_10E4C3C0()
{
}
