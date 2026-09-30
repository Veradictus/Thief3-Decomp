// Game/Unsorted_10A8AC40.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern const char DAT_10e47660[];

class Class_109081E0
{
public:
    Class_109081E0(const char* In);
    ~Class_109081E0();
    Class_109081E0& FUN_1090a590(const char* In);

    char* Unknown00;
};

class Class_10A036A0
{
public:
    Class_10A036A0& FUN_10a036a0(const Class_10A036A0& Other);

    char Unknown00[0x10];
};

class Class_10E6C620
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
    virtual void FUN_10a8b080(Class_10E6C620* Other);

    Class_10A036A0 Unknown04;
    Class_109081E0 Unknown14;
};

// FUNCTION: 0x10A8B080 ?FUN_10a8b080@Class_10E6C620@@UAEXPAV1@@Z
void Class_10E6C620::FUN_10a8b080(Class_10E6C620* Other)
{
    Unknown14.FUN_1090a590(DAT_10e47660);
    Unknown04.FUN_10a036a0(Other->Unknown04);
}
