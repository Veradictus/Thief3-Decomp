// Game/Unsorted_10BB8360_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Object_10AAF570
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
    virtual int Virtual38();
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
    virtual void Virtual58(int A, float B, int C);
};

class Class_10AAF570
{
public:
    int FUN_10aaf570();
};

struct Struct_10FF66BC
{
    int Flags;
    char Unknown04[16];
};

extern Struct_10FF66BC DAT_10ff66bc[];

class Class_10BB8360
{
public:
    void FUN_10bb8360(int A, float B, int C);

    char Unknown00[0xC];
    Class_10AAF570* Unknown0C;
};

// FUNCTION: 0x10BB8360 ?FUN_10bb8360@Class_10BB8360@@QAEXHMH@Z
void Class_10BB8360::FUN_10bb8360(int A, float B, int C)
{
    if (Unknown0C && (DAT_10ff66bc[((Object_10AAF570*)Unknown0C->FUN_10aaf570())->Virtual38()].Flags & 4))
        return;
    ((Object_10AAF570*)Unknown0C->FUN_10aaf570())->Virtual58(A, B, C);
}
