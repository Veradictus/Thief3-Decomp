// Game/Unsorted_10A93D00.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10A93D00
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual int Virtual5(int A);
    virtual void Virtual6();
    virtual int Virtual7(int A);
};

class Class_10D52BD0
{
public:
    void FUN_10d52bd0();
};

Class_10D52BD0* __stdcall FUN_10d52dd0(int A, int B);

class Class_10E6CCD8
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual int FUN_10a93d00(int A, int B, Class_10A93D00* C);
};

// FUNCTION: 0x10A93D00 ?FUN_10a93d00@Class_10E6CCD8@@UAEHHHPAVClass_10A93D00@@@Z
int Class_10E6CCD8::FUN_10a93d00(int A, int B, Class_10A93D00* C)
{
    int First = C->Virtual5(0);
    int Second = C->Virtual7(1);
    FUN_10d52dd0(First, Second)->FUN_10d52bd0();
    return 1;
}
