// Game/Unsorted_10B879C0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10D9FD70
{
public:
    bool FUN_10d9fd70();
};

class Class_10B8CCD0
{
public:
    void FUN_10b8ccd0(int A);

    char Unknown00[0x19];
    bool Unknown19;
};

class Class_10E893B0
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
    virtual bool FUN_10b87e40(int A);

    char Unknown04[0xC];
    Class_10D9FD70* Unknown10;
    char Unknown14[0x64];
    Class_10B8CCD0* Unknown78;
};

// FUNCTION: 0x10B87E40 ?FUN_10b87e40@Class_10E893B0@@UAE_NH@Z
bool Class_10E893B0::FUN_10b87e40(int A)
{
    if (Unknown10->FUN_10d9fd70())
    {
        Class_10B8CCD0* Obj = Unknown78;
        if (Obj)
            Obj->FUN_10b8ccd0(A);
        return Unknown78 ? Unknown78->Unknown19 : false;
    }
    return false;
}
