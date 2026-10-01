// Game/Unsorted_10B88900_3.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10CAFD00
{
public:
    void FUN_10cafd00(int A);
};

class Class_10D9B090
{
public:
    char Unknown00[4];
    Class_10CAFD00* Unknown04;
};

Class_10D9B090* FUN_10d9dcb0();

class Class_10E89AA0
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
    virtual void FUN_10d9fd80();
};

class Class_10E894C8 : public Class_10E89AA0
{
public:
    virtual void FUN_10b8a7f0();

    char Unknown04[0x30];
    bool Unknown34;
    char Unknown35[0x1B];
    int Unknown50;
};

// FUNCTION: 0x10B8A7F0 ?FUN_10b8a7f0@Class_10E894C8@@UAEXXZ
void Class_10E894C8::FUN_10b8a7f0()
{
    if (Unknown34)
    {
        Class_10E89AA0::FUN_10d9fd80();
        return;
    }
    Class_10D9B090* Manager = FUN_10d9dcb0();
    Manager->Unknown04->FUN_10cafd00(Unknown50);
}
