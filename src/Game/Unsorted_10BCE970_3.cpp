// Game/Unsorted_10BCE970_3.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class TimeManager
{
public:
    static TimeManager* Instance();
    double GetGameTime();
};

class Class_10C30640
{
public:
    void FUN_10c30640();
};

class Class_10BC4BF0
{
public:
    virtual void Virtual0();

    int FUN_10bc4bf0();
};

class Class_10E94578 : public Class_10BC4BF0
{
public:
    void FUN_10bc5b50();
};

class Class_10E92A00 : public Class_10E94578
{
public:
    virtual void FUN_10bce970();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5();
    virtual void Virtual6();
    virtual void Virtual7();
    virtual void Virtual8();
    virtual void Virtual9();
    virtual void Virtual10();
    virtual void Virtual11();
    virtual void Virtual12();
    virtual void Virtual13();
    virtual void Virtual14();
    virtual void Virtual15();
    virtual void Virtual16();
    virtual void Virtual17();
    virtual void Virtual18();
    virtual void Virtual19();
    virtual void Virtual20();
    virtual void Virtual21();
    virtual void Virtual22();
    virtual void FUN_10bcecd0(int A, int B, int C, int D, int E);

    char Unknown04[0x3C];
    double Unknown40;
    double Unknown48;
    float Unknown50;
};

// FUNCTION: 0x10BCE970 ?FUN_10bce970@Class_10E92A00@@UAEXXZ
void Class_10E92A00::FUN_10bce970()
{
    if (Unknown40 < 0.0)
    {
        Unknown40 = TimeManager::Instance()->GetGameTime();
        Unknown48 = Unknown40 + Unknown50;
        ((Class_10C30640*)FUN_10bc4bf0())->FUN_10c30640();
    }
}
