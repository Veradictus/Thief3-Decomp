// Game/Unsorted_10B8EC50_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_109081E0
{
public:
    Class_109081E0(const char* In);
    ~Class_109081E0();

    char* Unknown00;
};

extern char DAT_10f05b98[][32];

class Class_10E89720
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual Class_109081E0 FUN_10b8eca0();

    int Unknown04;
};

// FUNCTION: 0x10B8ECA0 ?FUN_10b8eca0@Class_10E89720@@UAE?AVClass_109081E0@@XZ
Class_109081E0 Class_10E89720::FUN_10b8eca0()
{
    return Class_109081E0(DAT_10f05b98[Unknown04]);
}
