// Game/Unsorted_10A2EE80.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10A2EF90 {
public:
    int Unknown00;
    int Unknown04;
    Class_10A2EF90* FUN_10a2ef90();
};

class Class_10E66368
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual bool FUN_10a2f0f0(int p1);

    char Unknown04[0x34];
    int Unknown38;
};

class Class_10E66300
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual int FUN_10a2f110(Class_10E66300* Other);

    int Unknown04;
    int Unknown08;
};

class Class_10A2F180 {
public:
    Class_10A2F180* FUN_10a2f180();

    int Unknown00;
    unsigned char Unknown04;
    int Unknown08;
    int Unknown0C;
    int Unknown10;
    int Unknown14;
};

extern void* DAT_10e6bb18[];

class Class_10E6BB18 {
public:
    Class_10E6BB18* FUN_10a2f3c0();

    void* Unknown00;
    int Unknown04;
    int Unknown08;
};

extern void* DAT_10e66310[];

class Class_10E66310 {
public:
    Class_10E66310* FUN_10a2f440();

    void* Unknown00;
    int Unknown04;
    int Unknown08;
};

extern void* DAT_10e6b93c[];

class Class_10E6B93C {
public:
    Class_10E6B93C* FUN_10a2fa50(int p1);

    void* Unknown00;
    int Unknown04;
};

// FUNCTION: 0x10A2EF90 ?FUN_10a2ef90@Class_10A2EF90@@QAEPAV1@XZ
Class_10A2EF90* Class_10A2EF90::FUN_10a2ef90()
{
    Unknown00 = 0;
    Unknown04 = 0;
    return this;
}

// FUNCTION: 0x10A2F0F0 ?FUN_10a2f0f0@Class_10E66368@@UAE_NH@Z
bool Class_10E66368::FUN_10a2f0f0(int p1)
{
    return Unknown38 == p1;
}

// FUNCTION: 0x10A2F110 ?FUN_10a2f110@Class_10E66300@@UAEHPAV1@@Z
int Class_10E66300::FUN_10a2f110(Class_10E66300* Other)
{
    if (Other->Unknown04 == Unknown04 && Other->Unknown08 == Unknown08)
        return 1;
    return 0;
}

// FUNCTION: 0x10A2F180 ?FUN_10a2f180@Class_10A2F180@@QAEPAV1@XZ
Class_10A2F180* Class_10A2F180::FUN_10a2f180()
{
    Unknown00 = 0;
    Unknown04 = 0;
    Unknown10 = -1;
    Unknown14 = 0;
    return this;
}

// FUNCTION: 0x10A2F3C0 ?FUN_10a2f3c0@Class_10E6BB18@@QAEPAV1@XZ
Class_10E6BB18* Class_10E6BB18::FUN_10a2f3c0()
{
    Unknown04 = 0;
    Unknown00 = DAT_10e6bb18;
    Unknown08 = 0;
    return this;
}

// FUNCTION: 0x10A2F440 ?FUN_10a2f440@Class_10E66310@@QAEPAV1@XZ
Class_10E66310* Class_10E66310::FUN_10a2f440()
{
    Unknown04 = 0;
    Unknown00 = DAT_10e66310;
    Unknown08 = 1;
    return this;
}

// FUNCTION: 0x10A2FA50 ?FUN_10a2fa50@Class_10E6B93C@@QAEPAV1@H@Z
Class_10E6B93C* Class_10E6B93C::FUN_10a2fa50(int p1)
{
    Unknown00 = DAT_10e6b93c;
    Unknown04 = p1;
    return this;
}
