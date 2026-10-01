// Game/Unsorted_109E3770.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Struct_109E3770
{
    int Unknown00;
    int Unknown04;
    int Unknown08;
};

class Class_10E5B2C0
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
    virtual void FUN_109e3770(const Struct_109E3770* In);

    char Unknown04[0x30];
    Struct_109E3770 Unknown34;
};

struct Struct_109E3790
{
    int Unknown00;
    int Unknown04;
    int Unknown08;
};

class Class_109E3790
{
public:
    void FUN_109e3790();

    char Unknown00[0x28];
    Struct_109E3790 Unknown28;
    Struct_109E3790 Unknown34;
};

// FUNCTION: 0x109E3770 ?FUN_109e3770@Class_10E5B2C0@@UAEXPBUStruct_109E3770@@@Z
void Class_10E5B2C0::FUN_109e3770(const Struct_109E3770* In)
{
    Unknown34 = *In;
}

// FUNCTION: 0x109E3790 ?FUN_109e3790@Class_109E3790@@QAEXXZ
void Class_109E3790::FUN_109e3790()
{
    Unknown34 = Unknown28;
}
