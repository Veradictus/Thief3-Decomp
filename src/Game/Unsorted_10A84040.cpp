// Game/Unsorted_10A84040.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10E6C364_Unknown10
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual int Virtual4(int A);
};

class Class_10E6C364
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual int FUN_10a84680(int A);

    char Unknown04[4];
    int Unknown08;
    char Unknown0C[4];
    Class_10E6C364_Unknown10** Unknown10;
};

// FUNCTION: 0x10A84680 ?FUN_10a84680@Class_10E6C364@@UAEHH@Z
int Class_10E6C364::FUN_10a84680(int A)
{
    for (int i = 0; i < Unknown08; i++)
    {
        if (Unknown10[i]->Virtual4(A))
            return 1;
    }
    return 0;
}
