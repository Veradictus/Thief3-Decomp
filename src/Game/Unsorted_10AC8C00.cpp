// Game/Unsorted_10AC8C00.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10990E20
{
public:
    bool FUN_10990e20();
};

class Class_10E6FC80
{
public:
    virtual void FUN_10ac8e80(int Type, Class_10990E20* Source, int C, int D);
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5(Class_10990E20* Source, int B, int C, int D);
};

// FUNCTION: 0x10AC8E80 ?FUN_10ac8e80@Class_10E6FC80@@UAEXHPAVClass_10990E20@@HH@Z
void Class_10E6FC80::FUN_10ac8e80(int Type, Class_10990E20* Source, int C, int D)
{
    if (Type == 0x3d && Source && Source->FUN_10990e20())
        Virtual5(Source, 0, 1, 0);
}
