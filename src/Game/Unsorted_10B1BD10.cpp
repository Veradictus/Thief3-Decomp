// Game/Unsorted_10B1BD10.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10B1D170
{
public:
    void FUN_10b1c520();
    void FUN_10b1c5c0();
    void FUN_10b1cab0();
    void FUN_10b1d170();
};

class Class_10B1BD70
{
public:
    void FUN_10b1bd70();
};

struct Struct_10AA3520
{
    char Unknown00[0xBC];
    Class_10B1BD70* UnknownBC;
};

extern Struct_10AA3520* DAT_10f35dec;

class Class_10E79488
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
    virtual void FUN_10b1be80(int A);
};

// FUNCTION: 0x10B1BE80 ?FUN_10b1be80@Class_10E79488@@UAEXH@Z
void Class_10E79488::FUN_10b1be80(int A)
{
    if (DAT_10f35dec)
    {
        Class_10B1BD70* Obj = DAT_10f35dec->UnknownBC;
        if (Obj)
            Obj->FUN_10b1bd70();
    }
}

// FUNCTION: 0x10B1D170 ?FUN_10b1d170@Class_10B1D170@@QAEXXZ
void Class_10B1D170::FUN_10b1d170()
{
    FUN_10b1c520();
    FUN_10b1c5c0();
    FUN_10b1cab0();
}
