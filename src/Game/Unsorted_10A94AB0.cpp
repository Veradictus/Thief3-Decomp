// Game/Unsorted_10A94AB0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10A174E0
{
public:
    virtual void Virtual0();
    virtual void Virtual1(int A, int B);
};

Class_10A174E0* FUN_10a18230();

class Class_10978090
{
public:
    int FUN_10978090();

    char Unknown00[4];
    int Unknown04;
};

class Class_10A93D00
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual Class_10978090* Virtual4(int A);
};

class Class_10E6CE1C
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual int FUN_10a94ab0(int A, int B, Class_10A93D00* C);
};

// FUNCTION: 0x10A94AB0 ?FUN_10a94ab0@Class_10E6CE1C@@UAEHHHPAVClass_10A93D00@@@Z
int Class_10E6CE1C::FUN_10a94ab0(int A, int B, Class_10A93D00* C)
{
    Class_10978090* First = C->Virtual4(0);
    Class_10978090* Second = C->Virtual4(1);
    Class_10A174E0* Manager = FUN_10a18230();
    int Id = First->Unknown04;
    Manager->Virtual1(Id, Second->FUN_10978090());
    return 1;
}
