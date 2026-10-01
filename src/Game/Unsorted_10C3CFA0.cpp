// Game/Unsorted_10C3CFA0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10C3CFC0
{
public:
    char Unknown00[0xC];
    int Unknown0C;
    int Unknown10;
    int Unknown14;
    void FUN_10c3cfc0(int p1, int p2, int p3);
};

class Class_10E9AFA4
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void FUN_10c3cfa0(int* p1, int* p2, int* p3);

    char Unknown04[8];
    int Unknown0C;
    int Unknown10;
    int Unknown14;
};

// FUNCTION: 0x10C3CFA0 ?FUN_10c3cfa0@Class_10E9AFA4@@UAEXPAH00@Z
void Class_10E9AFA4::FUN_10c3cfa0(int* p1, int* p2, int* p3)
{
    *p1 = Unknown10;
    *p2 = Unknown0C;
    *p3 = Unknown14;
}

// FUNCTION: 0x10C3CFC0 ?FUN_10c3cfc0@Class_10C3CFC0@@QAEXHHH@Z
void Class_10C3CFC0::FUN_10c3cfc0(int p1, int p2, int p3)
{
    Unknown10 = p1;
    Unknown0C = p2;
    Unknown14 = p3;
}
