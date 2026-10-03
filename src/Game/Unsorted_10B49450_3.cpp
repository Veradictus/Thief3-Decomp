// Game/Unsorted_10B49450_3.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10B39700
{
public:
    void FUN_10b39700();
};

class Class_10AA82D0
{
public:
    virtual void Virtual0();

    int FUN_10aa82d0();
};

class Class_10E81548 : public Class_10AA82D0
{
public:
    bool FUN_10b3af60(int A);
};

class Class_10E7E658 : public Class_10E81548
{
public:
    virtual void FUN_10b49990(int A);
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();

    void FUN_10b49640(int A);
};

// FUNCTION: 0x10B49990 ?FUN_10b49990@Class_10E7E658@@UAEXH@Z
void Class_10E7E658::FUN_10b49990(int A)
{
    if (!FUN_10b3af60(A))
        ((Class_10B39700*)FUN_10aa82d0())->FUN_10b39700();
    FUN_10b49640(A);
    Virtual4();
}
