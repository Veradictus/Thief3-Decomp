// Game/Unsorted_10B137C0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
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
    ~Class_10B7C000();

    void FUN_10ad5310();
};

class Class_10E5B578
{
public:
    virtual int Virtual0(int A, int B) = 0;
};

class Class_10E4B040 : public Class_10B7C000, public Class_10E5B578
{
public:
    ~Class_10E4B040();
};

class Class_10E78A30 : public Class_10E4B040
{
public:
    ~Class_10E78A30();

    virtual int Virtual0(int A, int B);
};

// FUNCTION: 0x10B13890 ??1Class_10E78A30@@QAE@XZ
Class_10E78A30::~Class_10E78A30()
{
    FUN_10ad5310();
}
