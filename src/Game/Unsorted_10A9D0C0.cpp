// Game/Unsorted_10A9D0C0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Object_10A9D0C0
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4(int A);
};

class Class_10E6D1FC
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual int FUN_10a9d0c0(int A, Object_10A9D0C0* B, int C);
};

// FUNCTION: 0x10A9D0C0 ?FUN_10a9d0c0@Class_10E6D1FC@@UAEHHPAVObject_10A9D0C0@@H@Z
int Class_10E6D1FC::FUN_10a9d0c0(int A, Object_10A9D0C0* B, int C)
{
    B->Virtual1();
    B->Virtual4(A);
    return 0;
}
