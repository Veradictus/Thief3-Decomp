// Game/Unsorted_10B9E430.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10C01CE0
{
public:
    void FUN_10c01ce0();
};

class Class_10BA9EC0
{
public:
    void* FUN_10ba9ec0();
};

class Class_10BA9EE0 : public Class_10BA9EC0
{
public:
    int FUN_10ba9ee0();
};

struct Class_10B9E410_Unknown0C
{
    char Unknown00[8];
    Class_10BA9EE0* Unknown08;
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
    virtual int Virtual11(Class_10B9E410_Unknown0C* A, int B);
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
    virtual int Virtual48(Class_10B9E410_Unknown0C* A, int B);
};

class Class_10B9E410
{
public:
    void FUN_10b9d740(int A);
    void FUN_10b9e660();
    void FUN_10b9e690(int A);

    char Unknown00[0xC];
    Class_10B9E410_Unknown0C* Unknown0C;
    char Unknown10[0x28];
    Class_10B9E410_Member* Unknown38;
};

// FUNCTION: 0x10B9E660 ?FUN_10b9e660@Class_10B9E410@@QAEXXZ
void Class_10B9E410::FUN_10b9e660()
{
    int Result = Unknown0C->Unknown08->FUN_10ba9ee0();
    if (Result)
    {
        int Next = Unknown38->Virtual11(Unknown0C, Result);
        if (Next)
            FUN_10b9d740(Next);
    }
}

// FUNCTION: 0x10B9E690 ?FUN_10b9e690@Class_10B9E410@@QAEXH@Z
void Class_10B9E410::FUN_10b9e690(int A)
{
    static_cast<Class_10C01CE0*>(Unknown0C->Unknown08->FUN_10ba9ec0())->FUN_10c01ce0();
    Class_10B9E410_Member* Obj = Unknown38;
    Class_10B9E410_Unknown0C* Key = Unknown0C;
    int Next = Obj->Virtual48(Key, A);
    if (Next)
        FUN_10b9d740(Next);
}
