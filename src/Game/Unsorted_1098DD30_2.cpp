// Game/Unsorted_1098DD30_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10E70A50
{
public:
    Class_10E70A50();

    virtual void FUN_10adb3a0();

    char Unknown04[0x28];
};

class Class_10993EC0 : public Class_10E70A50
{
public:
    Class_10993EC0()
    {
        UnknownB0 = 0;
        UnknownB4 = 0;
        UnknownB8 = 0;
    }

    virtual void FUN_10adb3a0();

    char Unknown2C[0x84];
    int UnknownB0;
    int UnknownB4;
    int UnknownB8;
};

class ASpecialOptions : public Class_10993EC0
{
public:
    ASpecialOptions();
};

class AMissingArch : public Class_10993EC0
{
public:
    AMissingArch();
};

class AObjSysTest : public Class_10993EC0
{
public:
    AObjSysTest();
};

class AObjSysTestChild : public Class_10993EC0
{
public:
    AObjSysTestChild();
};

// FUNCTION: 0x1098DDB0 ??0ASpecialOptions@@QAE@XZ
ASpecialOptions::ASpecialOptions()
{
}

// FUNCTION: 0x1098DE60 ??0AMissingArch@@QAE@XZ
AMissingArch::AMissingArch()
{
}

// FUNCTION: 0x1098DF10 ??0AObjSysTest@@QAE@XZ
AObjSysTest::AObjSysTest()
{
}

// FUNCTION: 0x1098DF40 ??0AObjSysTestChild@@QAE@XZ
AObjSysTestChild::AObjSysTestChild()
{
}
