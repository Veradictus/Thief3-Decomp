// Game/Unsorted_10A8AC70.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10A8AC70;

class Object_10A8AC70
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5();
    virtual void Virtual6();
    virtual bool Virtual7(Class_10A8AC70* A);
};

class Class_10A8AC70
{
public:
    bool Check()
    {
        return Unknown00 && Unknown00->Virtual7(this);
    }

    bool FUN_10a8ac70();

    Object_10A8AC70* Unknown00;
};

// FUNCTION: 0x10A8AC70 ?FUN_10a8ac70@Class_10A8AC70@@QAE_NXZ
bool Class_10A8AC70::FUN_10a8ac70()
{
    return !Check();
}
