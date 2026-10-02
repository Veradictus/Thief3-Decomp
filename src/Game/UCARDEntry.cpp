// Game/UCARDEntry.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
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

class UCARDEntry : public Class_10B7C000
{
public:
    ~UCARDEntry();
};

// FUNCTION: 0x1098AA90 ??1UCARDEntry@@QAE@XZ
UCARDEntry::~UCARDEntry()
{
    FUN_10ad5310();
}
