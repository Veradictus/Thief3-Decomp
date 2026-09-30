// Game/Unsorted_10A3A200.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Struct_10919190
{
    float Unknown00[16];
};

class Class_10A3A300_Primary
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5();
    virtual void Virtual6();
};

class Class_10E66718
{
public:
    virtual void FUN_10a3a300(int A);
    void FUN_10948bd0();

    Struct_10919190 Unknown04;
    char Unknown44[0x18];
    int Unknown5C;
    char Unknown60[0xD0];
    bool Unknown130;
};

class Class_10A3A300 : public Class_10A3A300_Primary, public Class_10E66718
{
public:
    virtual void FUN_10a3a300(int A);
};

class Class_10A3A4C0
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual int Virtual4();
};

class Class_10E6678C
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual bool FUN_10a3a4c0();

    char Unknown04[0xE4];
    int Unknown0E8;
    char Unknown0EC[4];
    Class_10A3A4C0** Unknown0F0;
};

// FUNCTION: 0x10A3A300 ?FUN_10a3a300@Class_10A3A300@@UAEXH@Z
void Class_10A3A300::FUN_10a3a300(int A)
{
    FUN_10948bd0();
    Unknown5C = 0;
    if (!Unknown130)
        Virtual6();
}

// FUNCTION: 0x10A3A4C0 ?FUN_10a3a4c0@Class_10E6678C@@UAE_NXZ
bool Class_10E6678C::FUN_10a3a4c0()
{
    if (Unknown0E8 == 0)
        return true;
    return (*Unknown0F0)->Virtual4() == 0;
}
