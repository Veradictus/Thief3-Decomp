// Game/Unsorted_10B35640.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10BAA6B0_Param;

class Class_10BABED0
{
public:
    bool FUN_10babed0(bool A);
};

Class_10BABED0* FUN_10baa6b0(Class_10BAA6B0_Param* Obj);

class Class_10C08940
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
    virtual Class_10BAA6B0_Param* Virtual8();
};

class Class_10978090
{
public:
    virtual void Virtual0();

    Class_10C08940* FUN_10978090();
};

class Class_10e7c360 : public Class_10978090
{
public:
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual bool FUN_10b35630(int p1);
    virtual int FUN_10b35640(int A, int B);
};

// FUNCTION: 0x10B35640 ?FUN_10b35640@Class_10e7c360@@UAEHHH@Z
int Class_10e7c360::FUN_10b35640(int A, int B)
{
    Class_10BAA6B0_Param* Obj = FUN_10978090()->Virtual8();
    return FUN_10baa6b0(Obj)->FUN_10babed0(false);
}
