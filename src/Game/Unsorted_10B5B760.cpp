// Game/Unsorted_10B5B760.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern void* DAT_10e82e90[];

class Class_10E81130
{
public:
    Class_10E81130* FUN_10b46080();

    void** Unknown00;
    char Unknown04[0x160];
};

class Class_10E82E90 : public Class_10E81130
{
public:
    Class_10E82E90* FUN_10b5b7b0();

    int Unknown164;
    int Unknown168[4];
    int Unknown178;
};

class Object_10B5B760
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
    virtual void Virtual49();
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
    virtual void Virtual63();
    virtual void Virtual64();
    virtual void Virtual65();
    virtual void Virtual66();
    virtual void Virtual67();
    virtual void Virtual68();
    virtual void Virtual69();
    virtual void Virtual70(int A);
};

class Class_10B5C440
{
public:
    void FUN_10b45ca0();
};

class Class_10B5B760 : public Class_10B5C440
{
public:
    void FUN_10b5b760();

    char Unknown00[0x164];
    Object_10B5B760* Unknown164;
    char Unknown168[8];
    Object_10B5B760** Unknown170;
};

// FUNCTION: 0x10B5B760 ?FUN_10b5b760@Class_10B5B760@@QAEXXZ
void Class_10B5B760::FUN_10b5b760()
{
    FUN_10b45ca0();
    if (Unknown164)
        Unknown164->Virtual70(0);
    for (int i = 0; i < 7; i++)
    {
        Object_10B5B760* Item = Unknown170[i];
        if (Item)
            Item->Virtual70(0);
    }
}

// FUNCTION: 0x10B5B7B0 ?FUN_10b5b7b0@Class_10E82E90@@QAEPAV1@XZ
Class_10E82E90* Class_10E82E90::FUN_10b5b7b0()
{
    FUN_10b46080();
    Unknown00 = DAT_10e82e90;
    Unknown164 = 0;
    for (int i = 0; i < 4; i++)
        Unknown168[i] = 0;
    Unknown178 = 1;
    return this;
}
