// Game/Unsorted_10B8ECD0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_109081E0
{
public:
    Class_109081E0(const char* In);
    ~Class_109081E0();

    char* Unknown00;
};

extern int DAT_10ff6600;

extern char DAT_10f05b98[][0x20];

class Class_10E89720
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
    virtual Class_109081E0 FUN_10b8ecd0();
};

// FUNCTION: 0x10B8ECD0 ?FUN_10b8ecd0@Class_10E89720@@UAE?AVClass_109081E0@@XZ
Class_109081E0 Class_10E89720::FUN_10b8ecd0()
{
    return Class_109081E0(DAT_10f05b98[DAT_10ff6600]);
}
