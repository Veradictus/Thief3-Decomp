// Game/Unsorted_10ABB4E0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10ABB4E0_Element
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual int Virtual4(int A);
};

class Class_10ABB4E0
{
public:
    int FUN_10abb4e0(int A);

    char Unknown00[4];
    int Unknown04;
    char Unknown08[4];
    Class_10ABB4E0_Element** Unknown0C;
};

// FUNCTION: 0x10ABB4E0 ?FUN_10abb4e0@Class_10ABB4E0@@QAEHH@Z
int Class_10ABB4E0::FUN_10abb4e0(int A)
{
    for (int i = 0; i < Unknown04; i++)
    {
        if (Unknown0C[i]->Virtual4(A))
            return i;
    }
    return -1;
}
