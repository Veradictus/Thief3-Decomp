// Game/Unsorted_10A62CF0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_1090A780
{
public:
    Class_1090A780(const Class_1090A780& Other);
    ~Class_1090A780();

    char* Unknown00;
};

class Class_109081E0
{
public:
    Class_109081E0& operator=(const Class_109081E0& Other);

    char* Unknown00;
};

class Class_10E6AC98
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
    virtual Class_1090A780 FUN_10a631d0();
    virtual void Virtual10();
    virtual void Virtual11();
    virtual void FUN_10c63a40(int p1);
    virtual Class_1090A780 FUN_10a63210();
    virtual void FUN_10a634a0(const Class_109081E0& A);

    char Unknown04[0xC];
    Class_1090A780 Unknown10;
    Class_109081E0 Unknown14;
    Class_1090A780 Unknown18;
    int Unknown1C;
};

// FUNCTION: 0x10A631D0 ?FUN_10a631d0@Class_10E6AC98@@UAE?AVClass_1090A780@@XZ
Class_1090A780 Class_10E6AC98::FUN_10a631d0()
{
    if (Unknown1C)
        return Unknown18;
    return Unknown10;
}
