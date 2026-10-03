// Game/Unsorted_10A8C0B0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10905A90_Member
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5(void* A);
};

Class_10905A90_Member* FUN_10905aa0();

class Class_109081E0
{
public:
    Class_109081E0(const char* In);
    Class_109081E0(const Class_109081E0& Other);
    ~Class_109081E0()
    {
        if (Unknown00)
        {
            char* Block = Unknown00 - 4;
            FUN_10905aa0()->Virtual5(Block);
            Unknown00 = 0;
        }
    }

    char* Unknown00;
};

class FName
{
public:
    Class_109081E0 FUN_10af9730() const;

    unsigned long Value;
};

extern const char DAT_10e5da10[];

class Class_10E6C6C4
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual Class_109081E0 FUN_10a8c140();

    FName Unknown04;
};

// FUNCTION: 0x10A8C140 ?FUN_10a8c140@Class_10E6C6C4@@UAE?AVClass_109081E0@@XZ
Class_109081E0 Class_10E6C6C4::FUN_10a8c140()
{
    if (!Unknown04.Value)
        return Class_109081E0(DAT_10e5da10);
    FName Name = Unknown04;
    return Class_109081E0(Name.FUN_10af9730());
}
