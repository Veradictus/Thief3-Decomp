// Game/ASpecialOptions.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10E70A50
{
public:
    virtual void FUN_10adb3a0();

    char Unknown04[0x28];
};

class Class_10B7C000 : public Class_10E70A50
{
public:
    void FUN_10ad5310();
};

class Class_10993EC0 : public Class_10B7C000
{
public:
    virtual void FUN_10adb3a0();
};

class AMetaData : public Class_10993EC0
{
public:
    ~AMetaData();
};

class ASpecialOptions : public AMetaData
{
public:
    ~ASpecialOptions();
};

// FUNCTION: 0x1098DE10 ??1ASpecialOptions@@QAE@XZ
ASpecialOptions::~ASpecialOptions()
{
    FUN_10ad5310();
}
