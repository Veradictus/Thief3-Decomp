// Game/Unsorted_10A63340_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10BFBD70
{
public:
    void FUN_10bfbd70(int NewCount);

    int Unknown00;
    int Unknown04;
    void* Unknown08;
};

class Class_10A63340 : public Class_10BFBD70
{
public:
    void FUN_10a63340(int Index);
    void FUN_10a63370(int A, int B, int C);
};

class Class_1090A780
{
public:
    Class_1090A780(const Class_1090A780& Other);
    ~Class_1090A780();

    char* Unknown00;
};

class Class_1091D800
{
public:
    Class_1090A780 FUN_1091d800(int A, int B);
};

class Class_10E6AC98
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual Class_1090A780 FUN_10a63440();

    char Unknown04[8];
    Class_1091D800* Unknown0C;
    char Unknown10[4];
    Class_1090A780 Unknown14;
    char Unknown18[4];
    int Unknown1C;
};

// FUNCTION: 0x10A63340 ?FUN_10a63340@Class_10A63340@@QAEXH@Z
void Class_10A63340::FUN_10a63340(int Index)
{
    if (Index != Unknown00 - 1)
        FUN_10a63370(Index + 1, Index, Unknown00 - Index - 1);
    FUN_10bfbd70(Unknown00 - 1);
}

// FUNCTION: 0x10A63440 ?FUN_10a63440@Class_10E6AC98@@UAE?AVClass_1090A780@@XZ
Class_1090A780 Class_10E6AC98::FUN_10a63440()
{
    if (Unknown1C)
        return Unknown14;
    return Unknown0C->FUN_1091d800(0, 2);
}
