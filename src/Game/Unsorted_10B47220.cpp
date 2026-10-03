// Game/Unsorted_10B47220.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10B22020;

class Object_10B4BC30;

class Class_10B395B0
{
public:
    void FUN_10b395b0(int A);
};

class Class_10B39700
{
public:
    void FUN_10b39700();
};

class Class_10AA82D0
{
public:
    virtual void Virtual0();

    int FUN_10aa82d0();

    char Unknown04[4];
    int Unknown08;
    int Unknown0C;
};

class Class_10E7E538 : public Class_10AA82D0
{
public:
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void FUN_10b483c0(Class_10B22020* A);
    virtual int Virtual4();
    virtual int FUN_10b48400(Object_10B4BC30* A, int B);

    int Unknown10;
};

class Class_10BFBD70
{
public:
    void FUN_109dff50(int Index);

    int Unknown00;
    int Unknown04;
    int* Unknown08;
};

class Class_10B47C50
{
public:
    void FUN_10b47b20(int A, float B, float C, int D, int E, bool F, bool G, float H);
    void FUN_10b47c50();

    char Unknown00[0x4C];
    Class_10BFBD70 Unknown4C;
};

// FUNCTION: 0x10B47C50 ?FUN_10b47c50@Class_10B47C50@@QAEXXZ
void Class_10B47C50::FUN_10b47c50()
{
    int Count = Unknown4C.Unknown00;
    if (Count > 0)
    {
        FUN_10b47b20(Unknown4C.Unknown08[Count - 1], -1.0f, 1.0f, 0x101, 0, true, false, -1.0f);
        Unknown4C.FUN_109dff50(Count - 1);
    }
}

// FUNCTION: 0x10B483C0 ?FUN_10b483c0@Class_10E7E538@@UAEXPAVClass_10B22020@@@Z
void Class_10E7E538::FUN_10b483c0(Class_10B22020* A)
{
    if (Unknown08 != 0x101)
    {
        ((Class_10B395B0*)FUN_10aa82d0())->FUN_10b395b0(Unknown08);
        ((Class_10B39700*)FUN_10aa82d0())->FUN_10b39700();
    }
    Unknown10 = 4;
}

// FUNCTION: 0x10B48400 ?FUN_10b48400@Class_10E7E538@@UAEHPAVObject_10B4BC30@@H@Z
int Class_10E7E538::FUN_10b48400(Object_10B4BC30* A, int B)
{
    if (Unknown10 == 3)
    {
        switch (B)
        {
        case 0x3c:
        case 0x3e:
        case 0x40:
            Unknown10 = 4;
            return 0;
        }
    }
    return Virtual4();
}
