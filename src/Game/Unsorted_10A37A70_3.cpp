// Game/Unsorted_10A37A70_3.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_1090A780
{
public:
    Class_1090A780(const Class_1090A780& Other);
    ~Class_1090A780();

    char* Unknown00;
};

class Class_109081E0 : public Class_1090A780
{
public:
    Class_109081E0(const char* In);
};

extern const char DAT_10e47660[];

class Class_10A37F30
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
    virtual float Virtual15();

    Class_109081E0 FUN_10a38f00();

    char Unknown04[0x598];
    int Unknown59C;
    char Unknown5A0[4];
    Class_109081E0* Unknown5A4;
};

// FUNCTION: 0x10A38F00 ?FUN_10a38f00@Class_10A37F30@@QAE?AVClass_109081E0@@XZ
Class_109081E0 Class_10A37F30::FUN_10a38f00()
{
    if (!Unknown59C)
        return Class_109081E0(DAT_10e47660);
    return *Unknown5A4;
}
