// Game/Unsorted_10BE1B30.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10BAA3A0
{
public:
    void* FUN_10baa3a0();
};

struct Struct_10BE1AD0
{
    char Unknown00[8];
    Class_10BAA3A0* Unknown08;
};

class Class_10E6C390
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual bool Virtual3();
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
    virtual int Virtual14();
    virtual int Virtual15(int A);
};

Class_10E6C390* FUN_10a86080();

class Class_10E95780
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
    virtual bool FUN_10be1b30(int A);
    virtual void Virtual14();
    virtual void Virtual15();
    virtual void Virtual16();
    virtual void Virtual17();
    virtual void Virtual18();
    virtual void Virtual19();
    virtual void Virtual20();
    virtual void Virtual21();
    virtual void Virtual22();
    virtual void FUN_10be1b00(int A, int B, int C, int D, int E);
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
    virtual void FUN_10be2780(int A);
    virtual void FUN_10be1ad0();

    void FUN_10be1a70();
    bool FUN_10be2380(void* Object, int A);

    Struct_10BE1AD0* Unknown04;
};

// FUNCTION: 0x10BE1B30 ?FUN_10be1b30@Class_10E95780@@UAE_NH@Z
bool Class_10E95780::FUN_10be1b30(int A)
{
    if (FUN_10a86080()->Virtual14() != 3 && FUN_10a86080()->Virtual15(A) == 3)
        return true;
    return false;
}
