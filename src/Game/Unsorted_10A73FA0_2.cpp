// Game/Unsorted_10A73FA0_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10E67938
{
public:
    Class_10E67938();
    ~Class_10E67938();

    virtual void FUN_10a74470(int A, int B, int C, int D);
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5();
    virtual bool FUN_10a4c4d0(int A);
    virtual void Virtual7();
};

class Class_10E6BB88 : public Class_10E67938
{
public:
    Class_10E6BB88();

    virtual void FUN_10a74470(int A, int B, int C, int D);
    virtual void Virtual1();
};

class Class_10F46DA0
{
public:
    virtual void Virtual0();
    virtual void Virtual1(Class_10E6BB88* Obj, int Type, int A, int B);
};

extern Class_10F46DA0* DAT_10f46da0;

// FUNCTION: 0x10A74410 ??0Class_10E6BB88@@QAE@XZ
Class_10E6BB88::Class_10E6BB88()
{
    DAT_10f46da0->Virtual1(this, 0x24, -1, -1);
}
