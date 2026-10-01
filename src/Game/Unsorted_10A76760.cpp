// Game/Unsorted_10A76760.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern void* DAT_10e6bd64[];

extern void* DAT_10e6bd60[];

class Class_10A79670
{
public:
    void FUN_10a79670();

    void* VTable;
    char Unknown04[0x14];
    void* Unknown18;
};

extern void* DAT_10e6bd68[];

class Class_10E6BD68
{
public:
    Class_10E6BD68* FUN_10a796a0();

    void** Unknown00;
    int Unknown04;
    int Unknown08;
    int Unknown0C;
    int Unknown10;
    int Unknown14;
    int Unknown18;
    int Unknown1C;
    int Unknown20;
    int Unknown24;
    int Unknown28;
    int Unknown2C;
    int Unknown30;
};

class Class_10E67938
{
public:
    virtual void FUN_10a4c470(int A, int B, int C, int D);
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5();
    virtual void Virtual6();
    virtual void Virtual7();
    virtual void Virtual8();
    virtual void Virtual9();
    virtual void Virtual10();
    virtual void Virtual11();
    virtual void Virtual12();
    virtual void Virtual13();
    virtual void Virtual14();
    virtual void Virtual15();
    virtual void Virtual16(int A, int B, int C);
};

class Class_10E6BD18 : public Class_10E67938
{
public:
    void FUN_10a790b0(int A, int B, int C, int D);
};

// FUNCTION: 0x10A790B0 ?FUN_10a790b0@Class_10E6BD18@@QAEXHHHH@Z
void Class_10E6BD18::FUN_10a790b0(int A, int B, int C, int D)
{
    if (A != 0x27)
    {
        Class_10E67938::FUN_10a4c470(A, B, C, D);
        return;
    }
    Virtual16(B, C, D);
}

// FUNCTION: 0x10A79670 ?FUN_10a79670@Class_10A79670@@QAEXXZ
void Class_10A79670::FUN_10a79670()
{
    VTable = DAT_10e6bd64;
    if (Unknown18)
        ::operator delete(Unknown18);
    Unknown18 = 0;
    VTable = DAT_10e6bd60;
}

// FUNCTION: 0x10A796A0 ?FUN_10a796a0@Class_10E6BD68@@QAEPAV1@XZ
Class_10E6BD68* Class_10E6BD68::FUN_10a796a0()
{
    Unknown00 = DAT_10e6bd68;
    Unknown04 = 0;
    Unknown08 = 0;
    Unknown0C = 0;
    Unknown10 = 0;
    Unknown14 = 0;
    Unknown18 = 0;
    Unknown1C = 0;
    Unknown20 = 0;
    Unknown24 = 0;
    Unknown28 = 0;
    Unknown2C = 0;
    Unknown30 = 0;
    return this;
}
