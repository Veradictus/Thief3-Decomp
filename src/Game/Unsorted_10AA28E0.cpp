// Game/Unsorted_10AA28E0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10978090
{
public:
    int FUN_10978090();
};

class Class_10AA28E0
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual Class_10978090* Virtual4(int A);
};

extern bool DAT_10f31a60;

class Class_10E6D430
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual int FUN_10aa28e0(int A, int B, Class_10AA28E0* C);
};

// FUNCTION: 0x10AA28E0 ?FUN_10aa28e0@Class_10E6D430@@UAEHHHPAVClass_10AA28E0@@@Z
int Class_10E6D430::FUN_10aa28e0(int A, int B, Class_10AA28E0* C)
{
    DAT_10f31a60 = C->Virtual4(0)->FUN_10978090() != 1;
    return 1;
}
