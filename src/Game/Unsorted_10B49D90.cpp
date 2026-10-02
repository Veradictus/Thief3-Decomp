// Game/Unsorted_10B49D90.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class AGarrett;

class Class_10B3AE70
{
public:
    virtual void Virtual0();
    virtual void Virtual1();

    void FUN_10b3ae70(AGarrett* Garrett);

    char Unknown04[0xC];
};

class Class_10AA9DC0
{
public:
    void* FUN_10aa9dc0();
};

class Class_10B19300 : public Class_10AA9DC0
{
};

Class_10B19300* FUN_10b190e0();

class Class_10E7E730 : public Class_10B3AE70
{
public:
    virtual void FUN_10b4a120(AGarrett* Garrett);

    void FUN_10b3b0b0(AGarrett* Garrett);

    void* Unknown10;
    float Unknown14;
};

class Class_10B3ADC0
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();

    void FUN_10b3ae90(AGarrett* Param);
    void FUN_10b3b130(AGarrett* Param);
};

class Class_10E7E6E8 : public Class_10B3ADC0
{
public:
    virtual void FUN_10b4a160(AGarrett* Param);
};

// FUNCTION: 0x10B4A120 ?FUN_10b4a120@Class_10E7E730@@UAEXPAVAGarrett@@@Z
void Class_10E7E730::FUN_10b4a120(AGarrett* Garrett)
{
    Unknown14 = -1.0f;
    Unknown10 = FUN_10b190e0()->FUN_10aa9dc0();
    FUN_10b3b0b0(Garrett);
    FUN_10b3ae70(Garrett);
}

// FUNCTION: 0x10B4A160 ?FUN_10b4a160@Class_10E7E6E8@@UAEXPAVAGarrett@@@Z
void Class_10E7E6E8::FUN_10b4a160(AGarrett* Param)
{
    FUN_10b3ae90(Param);
    FUN_10b3b130(Param);
}
