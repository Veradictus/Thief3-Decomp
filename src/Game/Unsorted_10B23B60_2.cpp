// Game/Unsorted_10B23B60_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10ABB6B0
{
public:
    void FUN_10abb6b0(int A);
};

class Class_10F3A3D8
{
public:
    char Unknown00[0xE8];
    Class_10ABB6B0* Unknown0E8;
};

extern Class_10F3A3D8* DAT_10f3a3d8;

class Class_10E78910
{
public:
    virtual void Virtual0();
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
    virtual void Virtual16();
    virtual void Virtual17();
    virtual void Virtual18();
    virtual void Virtual19();
    virtual void Virtual20();
    virtual void Virtual21();
    virtual void Virtual22();
    virtual void Virtual23();
    virtual void Virtual24();
    virtual void Virtual25();
    virtual void Virtual26();
    virtual void Virtual27();
    virtual void Virtual28();
    virtual void Virtual29();
    virtual void Virtual30();
    virtual void FUN_10b23b60(int A);

    void FUN_1098a410(int A);
};

class Class_10E7A9C0;

class Class_10B152C0
{
public:
    void FUN_10b152c0(int p1, Class_10E7A9C0* p2);
};

class Class_10E7A9C0
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5();
    virtual void Virtual6();
    virtual void Virtual7();
    virtual void Virtual8();
    virtual void Virtual9();
    virtual void FUN_10b248d0(Class_10B152C0* p1);
};

class Class_10B24D00
{
public:
    void FUN_10b24d00(int p1, unsigned char p2);
    char Unknown00[4];
    int Unknown04;
    int Unknown08;
    char Unknown0C[4];
    int Unknown10;
    int Unknown14;
};

class Class_10B24D20
{
public:
    char Unknown00[0x2C];
    int Unknown2C;
    int Unknown30;

    void FUN_10b24d20(int p1);
};

class Class_10B24D30
{
public:
    void FUN_10b24d30(int Mode);

    char Unknown00[4];
    int Unknown04;
    int Unknown08;
    char Unknown0C[4];
    int Unknown10;
    int Unknown14;
    char Unknown18[0x14];
    int Unknown2C;
    int Unknown30;
};

// FUNCTION: 0x10B23B60 ?FUN_10b23b60@Class_10E78910@@UAEXH@Z
void Class_10E78910::FUN_10b23b60(int A)
{
    FUN_1098a410(A);
    if (DAT_10f3a3d8->Unknown0E8)
        DAT_10f3a3d8->Unknown0E8->FUN_10abb6b0(A);
}

// FUNCTION: 0x10B248D0 ?FUN_10b248d0@Class_10E7A9C0@@UAEXPAVClass_10B152C0@@@Z
void Class_10E7A9C0::FUN_10b248d0(Class_10B152C0* p1)
{
    p1->FUN_10b152c0(0xef, this);
}

// FUNCTION: 0x10B24D00 ?FUN_10b24d00@Class_10B24D00@@QAEXHE@Z
void Class_10B24D00::FUN_10b24d00(int p1, unsigned char p2)
{
    Unknown10 = p2;
    Unknown14 = p2;
    Unknown04 = p1;
    Unknown08 = p1;
}

// FUNCTION: 0x10B24D20 ?FUN_10b24d20@Class_10B24D20@@QAEXH@Z
void Class_10B24D20::FUN_10b24d20(int p1)
{
    Unknown2C = p1;
    Unknown30 = p1;
}

// FUNCTION: 0x10B24D30 ?FUN_10b24d30@Class_10B24D30@@QAEXH@Z
void Class_10B24D30::FUN_10b24d30(int Mode)
{
    if (Mode == 2)
    {
        Unknown2C = 0;
        Unknown30 = 0;
        return;
    }
    bool IsZero = (Mode == 0);
    Unknown10 = IsZero;
    Unknown14 = IsZero;
    Unknown04 = 0;
    Unknown08 = 0;
}
