// Game/Unsorted_10C26370.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

// Ion Storm's string (0x109081E0): a char pointer, null when default constructed.
class Class_109081E0
{
public:
    ~Class_109081E0();

    char* Unknown00;
};

class Class_109B6D50
{
public:
    void FUN_109bf5f0(int A, const Class_109081E0& B);
};

class Class_10E9925C
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
    virtual bool Virtual8();

    Class_109B6D50* FUN_10c26490();

    char Unknown04[8];
    int Unknown0C;
    Class_109081E0 Unknown10;
    char Unknown14[0x20];
    bool Unknown34;
};

class Class_10E992D4 : public Class_10E9925C
{
public:
    void FUN_10c265c0();
};

// FUNCTION: 0x10C265C0 ?FUN_10c265c0@Class_10E992D4@@QAEXXZ
void Class_10E992D4::FUN_10c265c0()
{
    if (FUN_10c26490() && Unknown0C >= 0 && !Virtual8())
    {
        FUN_10c26490()->FUN_109bf5f0(Unknown0C, Unknown10);
        Unknown34 = true;
    }
}
