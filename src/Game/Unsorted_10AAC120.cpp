// Game/Unsorted_10AAC120.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10E6DA90
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5();
    virtual void Virtual6();
    virtual void FUN_10aac110(int param);
    virtual void Virtual8();
    virtual bool FUN_10aace40(int Kind);
};

// FUNCTION: 0x10AACE40 ?FUN_10aace40@Class_10E6DA90@@UAE_NH@Z
bool Class_10E6DA90::FUN_10aace40(int Kind)
{
    switch (Kind)
    {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 0xC:
    case 0xD:
    case 0xE:
        return true;
    }
    return false;
}
