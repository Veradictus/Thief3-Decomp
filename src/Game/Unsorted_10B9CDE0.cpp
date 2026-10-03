// Game/Unsorted_10B9CDE0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10B9E410_Item
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual int Virtual3();
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
    virtual void Virtual31();
    virtual void Virtual32();
    virtual void Virtual33();
    virtual void Virtual34();
};

class Class_10B9E410_Member;

class Class_10B9E410
{
public:
    void FUN_10b9cf60();
    void FUN_10b9cfa0();

    Class_10B9E410_Item* Top()
    {
        if (Unknown10 == 0)
            return 0;
        return Unknown18[Unknown10 - 1];
    }

    char Unknown00[0xC];
    int Unknown0C;
    int Unknown10;
    char Unknown14[4];
    Class_10B9E410_Item** Unknown18;
    int Unknown1C;
    int Unknown20;
    char Unknown24[0x14];
    Class_10B9E410_Member* Unknown38;
};

// FUNCTION: 0x10B9CF60 ?FUN_10b9cf60@Class_10B9E410@@QAEXXZ
void Class_10B9E410::FUN_10b9cf60()
{
    Unknown1C = 0;
    if (Top()->Virtual3() == 0x11)
        Top()->Virtual34();
}

// FUNCTION: 0x10B9CFA0 ?FUN_10b9cfa0@Class_10B9E410@@QAEXXZ
void Class_10B9E410::FUN_10b9cfa0()
{
    Unknown20 = 0;
    if (Top()->Virtual3() == 0x12)
        Top()->Virtual34();
}
