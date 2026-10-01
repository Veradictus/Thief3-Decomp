// Game/Unsorted_10C382F0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Object_10BCE8D0
{
public:
    virtual void Virtual0();
    virtual void Virtual1(void* Data, int Size);
};

class Class_10E9AF04
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
    virtual void Virtual8();
    virtual void Virtual9();
    virtual void FUN_10c38400(Object_10BCE8D0* A);

    void FUN_10c372e0(Object_10BCE8D0* A);

    char Unknown04[0x90];
    int Unknown94;
};

// FUNCTION: 0x10C38400 ?FUN_10c38400@Class_10E9AF04@@UAEXPAVObject_10BCE8D0@@@Z
void Class_10E9AF04::FUN_10c38400(Object_10BCE8D0* A)
{
    FUN_10c372e0(A);
    A->Virtual1(&Unknown94, 4);
}
