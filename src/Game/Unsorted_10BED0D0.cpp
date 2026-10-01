// Game/Unsorted_10BED0D0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10E94578
{
public:
    virtual void Virtual0();

    void FUN_10bc5b50();
};

class Class_10E975A0 : public Class_10E94578
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

    void FUN_10bece10();

    char Unknown04[0x40];
};

class Class_10E97258 : public Class_10E975A0
{
public:
    virtual void FUN_10bed130();

    int Unknown44;
};

extern void* DAT_10e97370[];

class Class_10E90D70
{
public:
    Class_10E90D70(int A, int B);

    void** Unknown00;
    int Unknown04[15];
};

class Class_10E97370 : public Class_10E90D70
{
public:
    Class_10E97370* FUN_10bed0d0(int A, int B, int C, int D, int E, int F);

    char Unknown40;
    int Unknown44;
    int Unknown48;
    int Unknown4C;
    int Unknown50;
};

// FUNCTION: 0x10BED0D0 ?FUN_10bed0d0@Class_10E97370@@QAEPAV1@HHHHHH@Z
Class_10E97370* Class_10E97370::FUN_10bed0d0(int A, int B, int C, int D, int E, int F)
{
    this->Class_10E90D70::Class_10E90D70(E, F);
    Unknown44 = A;
    Unknown48 = B;
    Unknown40 = 1;
    Unknown00 = DAT_10e97370;
    Unknown4C = C;
    Unknown50 = D;
    return this;
}

// FUNCTION: 0x10BED130 ?FUN_10bed130@Class_10E97258@@UAEXXZ
void Class_10E97258::FUN_10bed130()
{
    if (Unknown44 == 0)
        FUN_10bc5b50();
    else
        FUN_10bece10();
}
