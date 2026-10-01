// Game/Unsorted_10B4BE00_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class AGarrett;

class Class_10B3ADC0
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();

    void FUN_10b3adc0(AGarrett* Param);
    void FUN_10b3ae90(AGarrett* Param);
    void FUN_10b3b130(AGarrett* Param);
};

class Class_10E7E778 : public Class_10B3ADC0
{
public:
    virtual void FUN_10b4be90(AGarrett* Param);
};

class Class_10B398B0
{
public:
    void FUN_10b398b0(int p1);
};

class Class_10AA82D0
{
public:
    virtual void Virtual0();

    int FUN_10aa82d0();
};

class Class_10E7EA00 : public Class_10AA82D0
{
public:
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual int Virtual4();
    virtual int FUN_10b4cc70(int A, int B);

    char Unknown04[0xC];
    int Unknown10;
};

extern void* DAT_10e81590[];

class Class_10B3ACB0
{
public:
    Class_10B3ACB0* FUN_10b3acb0();

    void** Unknown00;
    char Unknown04[0x0C];
};

class Class_10E81590 : public Class_10B3ACB0
{
public:
    Class_10E81590* FUN_10b4ccf0();

    bool Unknown10;
    bool Unknown11;
};

// FUNCTION: 0x10B4BE90 ?FUN_10b4be90@Class_10E7E778@@UAEXPAVAGarrett@@@Z
void Class_10E7E778::FUN_10b4be90(AGarrett* Param)
{
    FUN_10b3b130(Param);
    FUN_10b3ae90(Param);
    FUN_10b3adc0(Param);
}

// FUNCTION: 0x10B4CC70 ?FUN_10b4cc70@Class_10E7EA00@@UAEHHH@Z
int Class_10E7EA00::FUN_10b4cc70(int A, int B)
{
    if (B == 0x6e)
        return Virtual4();
    ((Class_10B398B0*)FUN_10aa82d0())->FUN_10b398b0(0);
    Unknown10 = 1;
    return 0x17;
}

// FUNCTION: 0x10B4CCF0 ?FUN_10b4ccf0@Class_10E81590@@QAEPAV1@XZ
Class_10E81590* Class_10E81590::FUN_10b4ccf0()
{
    FUN_10b3acb0();
    Unknown10 = false;
    Unknown11 = false;
    Unknown00 = DAT_10e81590;
    return this;
}
