// Game/Unsorted_10A8A6B0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_109081E0
{
public:
    Class_109081E0(const char* In);
    ~Class_109081E0();

    char* Unknown00;
};

extern const char DAT_10e6c100[];

class Class_10E6C5D0
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
    virtual Class_109081E0 FUN_10a8a6b0();

    Class_10E6C5D0* Unknown04;
};

// FUNCTION: 0x10A8A6B0 ?FUN_10a8a6b0@Class_10E6C5D0@@UAE?AVClass_109081E0@@XZ
Class_109081E0 Class_10E6C5D0::FUN_10a8a6b0()
{
    if (!Unknown04)
        return Class_109081E0(DAT_10e6c100);
    return Unknown04->FUN_10a8a6b0();
}
