// Game/Unsorted_10B154E0_3.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10E5B7C8
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual bool FUN_109e3c60(int p1);

    char Unknown04[0x90];
    int Unknown94;
};

class Class_10E79228 : public Class_10E5B7C8
{
public:
    virtual bool FUN_10b155b0(int p1);

    char Unknown98[0x1C4];
    bool Unknown25C;
};

// FUNCTION: 0x10B155B0 ?FUN_10b155b0@Class_10E79228@@UAE_NH@Z
bool Class_10E79228::FUN_10b155b0(int p1)
{
    if (Unknown25C)
        return false;
    return Class_10E5B7C8::FUN_109e3c60(p1);
}
