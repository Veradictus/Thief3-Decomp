// Game/Unsorted_10A58C30.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10A53220
{
public:
    virtual void Virtual0();
    virtual bool Virtual1();

    void FUN_10a53220(float A);
};

class Class_10E69050
{
public:
    virtual void Virtual0();
    virtual int FUN_10a58bb0();
    virtual void FUN_10a58be0();
    virtual int FUN_10a58c10(int A);
    virtual void Virtual4();
    virtual void FUN_10a58c30(float A);

    char Unknown04[8];
    int Unknown0C;
    int Unknown10;
    Class_10A53220** Unknown14;
    int Unknown18;
};

// FUNCTION: 0x10A58C30 ?FUN_10a58c30@Class_10E69050@@UAEXM@Z
void Class_10E69050::FUN_10a58c30(float A)
{
    Unknown14[Unknown18]->FUN_10a53220(A);
    if (Unknown14[Unknown18]->Virtual1())
    {
        if (Unknown18 + 1 < Unknown0C)
            Unknown18++;
    }
}
