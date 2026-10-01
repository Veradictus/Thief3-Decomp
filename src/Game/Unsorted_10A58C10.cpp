// Game/Unsorted_10A58C10.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10A58C10Item
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3(int A);
};

class Class_10E69050
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual int FUN_10a58c10(int A);

    char Unknown04[0x10];
    Class_10A58C10Item** Unknown14;
    int Unknown18;
};

// FUNCTION: 0x10A58C10 ?FUN_10a58c10@Class_10E69050@@UAEHH@Z
int Class_10E69050::FUN_10a58c10(int A)
{
    Unknown14[Unknown18]->Virtual3(A);
    return A;
}
