// Game/Unsorted_10BE9D40.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Object_10BEBDC0
{
public:
    virtual int Virtual0();
};

class Class_10E94578
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
    virtual void FUN_10bcac50(int A, int B, int C, int D, int E);
};

class Class_10E970F0 : public Class_10E94578
{
public:
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
    virtual void FUN_10bebdc0(Object_10BEBDC0* A);

    void FUN_10bebc70();

    char Unknown04[0x60];
    bool Unknown64;
};

// FUNCTION: 0x10BEBDC0 ?FUN_10bebdc0@Class_10E970F0@@UAEXPAVObject_10BEBDC0@@@Z
void Class_10E970F0::FUN_10bebdc0(Object_10BEBDC0* A)
{
    if (!Unknown64)
    {
        switch (A->Virtual0())
        {
        case 0:
        case 9:
        case 11:
        case 12:
        case 13:
            FUN_10bebc70();
            break;
        }
    }
}
