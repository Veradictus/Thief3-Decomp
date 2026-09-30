// Game/Class_10EA2920.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern char DAT_10ea2a60[];

extern char DAT_10e475dc[];

int FUN_10aeb200(const char* In);

void FUN_10af37a0(int Param, const char* Format, int Value);

class Class_10EA2920
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5();
    virtual void Virtual6();
    virtual void Virtual7();
    virtual void Virtual8();
    virtual void FUN_10ca47c0(int Param);
};

// FUNCTION: 0x10CA47C0 ?FUN_10ca47c0@Class_10EA2920@@UAEXH@Z
void Class_10EA2920::FUN_10ca47c0(int Param)
{
    FUN_10af37a0(Param, DAT_10e475dc, FUN_10aeb200(DAT_10ea2a60));
}
