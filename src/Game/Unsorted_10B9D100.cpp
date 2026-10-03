// Game/Unsorted_10B9D100.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10BC9B10
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
    virtual void Virtual44();
    virtual void Virtual45();
    virtual void Virtual46();
    virtual void Virtual47();
    virtual void Virtual48();
    virtual void Virtual49(int A);
    virtual void Virtual50();
    virtual void Virtual51();
    virtual void Virtual52();
    virtual void Virtual53();
    virtual void Virtual54();
    virtual void Virtual55();
    virtual void Virtual56();
    virtual void Virtual57();
    virtual void Virtual58();
    virtual void Virtual59();
    virtual void Virtual60();
    virtual void Virtual61();
    virtual void Virtual62();
    virtual bool Virtual63();

    void FUN_10bc9b10(int A, int B, int C);
};

struct Struct_10AA3520
{
    char Unknown00[8];
    int Unknown08;
};

extern Struct_10AA3520* DAT_10f35dec;

class Class_10B9D100
{
public:
    void FUN_10b9d100(int A);
    void FUN_10b9d150(int A);

    char Unknown00[0x10];
    int Unknown10;
    char Unknown14[4];
    Class_10BC9B10** Unknown18;
};

// FUNCTION: 0x10B9D100 ?FUN_10b9d100@Class_10B9D100@@QAEXH@Z
void Class_10B9D100::FUN_10b9d100(int A)
{
    if (Unknown10)
    {
        Class_10BC9B10* Item = Unknown18[Unknown10 - 1];
        if (Item && Item->Virtual63())
            (Unknown10 == 0 ? 0 : Unknown18[Unknown10 - 1])->FUN_10bc9b10(A, 0x14, DAT_10f35dec->Unknown08);
    }
}

// FUNCTION: 0x10B9D150 ?FUN_10b9d150@Class_10B9D100@@QAEXH@Z
void Class_10B9D100::FUN_10b9d150(int A)
{
    for (int i = 0; i < Unknown10; i++)
        Unknown18[i]->Virtual49(A);
}
