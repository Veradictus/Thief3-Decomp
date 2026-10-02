// Game/Unsorted_10BC4BF0_3.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Struct_10BC4C10
{
    char Unknown00[0x2C];
    char Unknown2C[4];
};

class Class_10E8BE68
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
    virtual void FUN_10bc4c10(Struct_10BC4C10* p1, int p2);

    void FUN_10bc4170(void* p1, int p2);
};

// FUNCTION: 0x10BC4C10 ?FUN_10bc4c10@Class_10E8BE68@@UAEXPAUStruct_10BC4C10@@H@Z
void Class_10E8BE68::FUN_10bc4c10(Struct_10BC4C10* p1, int p2)
{
    if (p1)
        FUN_10bc4170(p1->Unknown2C, p2);
}
