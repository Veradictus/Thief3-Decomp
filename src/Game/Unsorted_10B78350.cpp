// Game/Unsorted_10B78350.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Object_10B79150
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
    virtual void Virtual56(int Mode);
};

class Class_10B79150
{
public:
    void FUN_10b79150(bool Flag);

    char Unknown00[0x158];
    Object_10B79150* Unknown158;
};

class Class_10905A90_Member
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5(int* Obj);
};

Class_10905A90_Member* FUN_10905aa0();

class Class_10B78380
{
public:
    void FUN_10b78380();

    char Unknown00[0x168];
    int* Unknown168;
};

class FArray
{
public:
    FArray() : Data(0), ArrayNum(0), ArrayMax(0) {}

    void* Data;
    int ArrayNum;
    int ArrayMax;
};

class Class_10E88AF8
{
public:
    Class_10E88AF8();

    virtual ~Class_10E88AF8();

    char Unknown04[0xE4];
    int Unknown0E8;
    char Unknown0EC[0x74];
};

class Class_10E886D0 : public Class_10E88AF8
{
public:
    Class_10E886D0();

    virtual ~Class_10E886D0();

    int Unknown160;
    int Unknown164;
    FArray Unknown168;
    int Unknown174;
    int Unknown178;
    int Unknown17C;
    int Unknown180;
    int Unknown184;
    int Unknown188;
    bool Unknown18C;
};

// FUNCTION: 0x10B78380 ?FUN_10b78380@Class_10B78380@@QAEXXZ
void Class_10B78380::FUN_10b78380()
{
    if (Unknown168)
    {
        int* Obj = Unknown168 - 1;
        FUN_10905aa0()->Virtual5(Obj);
        Unknown168 = 0;
    }
}

// FUNCTION: 0x10B78780 ??0Class_10E886D0@@QAE@XZ
Class_10E886D0::Class_10E886D0()
    : Unknown160(0), Unknown164(0), Unknown174(0), Unknown17C(0), Unknown180(0), Unknown184(0),
      Unknown188(0), Unknown18C(false)
{
    Unknown178 = 0x40;
    Unknown0E8 = 0x26;
}

// FUNCTION: 0x10B790C0 ??_GClass_10E886D0@@UAEPAXI@Z
// Compiler-generated: emitted with the class's vtable by 0x10B78780's definition in this unit.

// FUNCTION: 0x10B79150 ?FUN_10b79150@Class_10B79150@@QAEX_N@Z
void Class_10B79150::FUN_10b79150(bool Flag)
{
    if (Unknown158)
        Unknown158->Virtual56(Flag ? 2 : 0);
}
