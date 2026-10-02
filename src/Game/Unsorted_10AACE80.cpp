// Game/Unsorted_10AACE80.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
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
    virtual void Virtual10();
    virtual int FUN_10aace80(int Kind);
};

// FUNCTION: 0x10AACE80 ?FUN_10aace80@Class_10E6DA90@@UAEHH@Z
int Class_10E6DA90::FUN_10aace80(int Kind)
{
    switch (Kind)
    {
    case 0:
    case 2:
        return 3;
    case 4:
        return 0xD;
    case 5:
        return 0xE;
    case 0xD:
        return 4;
    case 0xE:
        return 5;
    case 1:
    case 6:
        return 0;
    case 7:
        return 6;
    case 8:
        return 0xA;
    case 9:
        return 0xB;
    case 0xA:
        return 8;
    case 0xB:
        return 9;
    case 3:
    case 0xC:
        return 2;
    }
    return 1;
}
