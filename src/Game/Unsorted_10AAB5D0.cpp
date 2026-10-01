// Game/Unsorted_10AAB5D0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10E6DA90
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5();
    virtual void Virtual6();
    virtual void FUN_10aac110(int param);

    char Unknown04[4];
    int Unknown08;
    char Unknown0C[8];
    bool Unknown14;
};

extern void* DAT_10e6da40[];

class Class_10E6C104
{
public:
    Class_10E6C104();

    void** Unknown00;
};

class Class_10E6DA40 : public Class_10E6C104
{
public:
    Class_10E6DA40* FUN_10aab5d0();

    char Unknown04[4];
    int Unknown08;
};

extern void* DAT_10e6da64[];

class Class_10E6DA64
{
public:
    Class_10E6DA64* FUN_10aab8b0();

    void** Unknown00;
    int Unknown04;
    int Unknown08;
    int Unknown0C;
    int Unknown10;
    int Unknown14;
    int Unknown18;
};

// FUNCTION: 0x10AAB5D0 ?FUN_10aab5d0@Class_10E6DA40@@QAEPAV1@XZ
Class_10E6DA40* Class_10E6DA40::FUN_10aab5d0()
{
    this->Class_10E6C104::Class_10E6C104();
    Unknown00 = DAT_10e6da40;
    Unknown08 = 3;
    return this;
}

// FUNCTION: 0x10AAB8B0 ?FUN_10aab8b0@Class_10E6DA64@@QAEPAV1@XZ
Class_10E6DA64* Class_10E6DA64::FUN_10aab8b0()
{
    Unknown00 = DAT_10e6da64;
    Unknown04 = 0;
    Unknown08 = 0;
    Unknown0C = 0;
    Unknown10 = 0;
    Unknown14 = 0;
    Unknown18 = 0;
    return this;
}

// FUNCTION: 0x10AAC110 ?FUN_10aac110@Class_10E6DA90@@UAEXH@Z
void Class_10E6DA90::FUN_10aac110(int param)
{
    Unknown08 = param;
    Unknown14 = true;
}
