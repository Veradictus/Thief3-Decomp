// Game/Unsorted_10B9D220.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10B9E410_Item
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual int Virtual3();
};

class Class_10B9E410_Member
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
    virtual int Virtual28(int A);
    virtual void Virtual29();
    virtual void Virtual30();
    virtual void Virtual31();
    virtual void Virtual32();
    virtual void Virtual33();
    virtual void Virtual34();
    virtual void Virtual35();
    virtual void Virtual36();
    virtual void Virtual37();
    virtual void Virtual38();
    virtual void Virtual39();
    virtual void Virtual40();
    virtual void Virtual41();
    virtual void Virtual42();
    virtual void Virtual43();
    virtual int Virtual44(int A, Class_10B9E410_Item* B, int C);
};

class Class_10B9E410
{
public:
    void FUN_10b9d740(int A);
    void FUN_10b9d8d0();
    void FUN_10b9dc80(int A);
    void FUN_10b9dcc0();

    char Unknown00[0xC];
    int Unknown0C;
    int Unknown10;
    char Unknown14[4];
    Class_10B9E410_Item** Unknown18;
    char Unknown1C[0x1C];
    Class_10B9E410_Member* Unknown38;
};

// FUNCTION: 0x10B9DC80 ?FUN_10b9dc80@Class_10B9E410@@QAEXH@Z
void Class_10B9E410::FUN_10b9dc80(int A)
{
    Class_10B9E410_Member* Obj = Unknown38;
    Class_10B9E410_Item* Top = Unknown10 == 0 ? 0 : Unknown18[Unknown10 - 1];
    int Key = Unknown0C;
    FUN_10b9d740(Obj->Virtual44(Key, Top, A));
}

// FUNCTION: 0x10B9DCC0 ?FUN_10b9dcc0@Class_10B9E410@@QAEXXZ
void Class_10B9E410::FUN_10b9dcc0()
{
    if (Unknown10)
    {
        Class_10B9E410_Item* Top = Unknown18[Unknown10 - 1];
        if (Top && Top->Virtual3() == 7)
            FUN_10b9d8d0();
    }
}
