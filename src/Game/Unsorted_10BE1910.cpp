// Game/Unsorted_10BE1910.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern const char DAT_10e5052c[];

enum EFindName
{
    FNAME_Find = 0,
    FNAME_Add = 1
};

class FName
{
public:
    FName(const char* Name, EFindName FindType = FNAME_Add);

    unsigned long Value;
};

class Class_10c7d570
{
public:
    void* FUN_10c7d570();
};

class Class_10A2C2F0
{
public:
    void FUN_10a2c2a0(void* A, int* B);
};

Class_10A2C2F0* FUN_10a2c6b0();

class Class_10bfb8d0
{
public:
    void FUN_10bfb8d0(int p1);
};

class Class_10FF667C
{
public:
    char Unknown00[0x28];
    Class_10bfb8d0* Unknown28;
};

extern Class_10FF667C* DAT_10ff667c;

class Class_10E95780_Unknown04
{
public:
    char Unknown00[8];
    Class_10c7d570* Unknown08;
};

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
    virtual void Virtual13();
    virtual void Virtual14();
    virtual void Virtual15();
    virtual void Virtual16();
    virtual void Virtual17();
    virtual void Virtual18();
    virtual void Virtual19();
    virtual void Virtual20();
    virtual void FUN_10be1970();

    Class_10E95780_Unknown04* Unknown04;
};

// FUNCTION: 0x10BE1970 ?FUN_10be1970@Class_10E95780@@UAEXXZ
void Class_10E95780::FUN_10be1970()
{
    FName Name(DAT_10e5052c, FNAME_Add);
    Class_10c7d570* Item = Unknown04->Unknown08;
    FUN_10a2c6b0()->FUN_10a2c2a0(Item->FUN_10c7d570(), (int*)&Name);
    DAT_10ff667c->Unknown28->FUN_10bfb8d0(3);
}
