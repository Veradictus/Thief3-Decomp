// Game/Unsorted_10A8B8C0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_1096C8D0
{
public:
    void FUN_1096c8d0();
};

class Class_10F3A1EC : public Class_1096C8D0
{
};

extern Class_10F3A1EC* DAT_10f3a1ec;

class Class_10E6C68C
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5();
    virtual void FUN_10a8bf80();
    virtual int FUN_10a8b860();
    virtual char** FUN_10a8bbc0(char** Out);

    int FUN_10a8bac0();
};

// FUNCTION: 0x10A8BF80 ?FUN_10a8bf80@Class_10E6C68C@@UAEXXZ
void Class_10E6C68C::FUN_10a8bf80()
{
    DAT_10f3a1ec->FUN_1096c8d0();
    while (FUN_10a8bac0())
        DAT_10f3a1ec->FUN_1096c8d0();
}
