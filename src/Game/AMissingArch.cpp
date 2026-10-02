// Game/AMissingArch.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
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

class AActor : public Class_10993EC0
{
public:
    ~AActor();
};

class AMissingArch : public AActor
{
public:
    ~AMissingArch();
};

// FUNCTION: 0x1098DEC0 ??1AMissingArch@@QAE@XZ
AMissingArch::~AMissingArch()
{
    FUN_10ad5310();
}
