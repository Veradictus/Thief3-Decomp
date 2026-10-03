// Game/Unsorted_10B7C770.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Object_10B7C7C0
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual int Virtual5(int A, int B);
};

class Class_10E4B178
{
public:
    virtual int FUN_10b7c7c0(int A, int B);

    char Unknown04[0x2C];
    int Unknown30;
    char Unknown34[4];
    Object_10B7C7C0** Unknown38;
};

// FUNCTION: 0x10B7C7C0 ?FUN_10b7c7c0@Class_10E4B178@@UAEHHH@Z
int Class_10E4B178::FUN_10b7c7c0(int A, int B)
{
    for (int i = 0; i < Unknown30; i++)
    {
        int Result = Unknown38[i]->Virtual5(A, B);
        if (Result)
            return Result;
    }
    return 0;
}
