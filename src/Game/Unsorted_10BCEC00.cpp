// Game/Unsorted_10BCEC00.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10E92C38
{
public:
    virtual void Virtual0();
    virtual void FUN_10bcef30();

    void FUN_10bced10();

    char Unknown04[0x44];
    bool Unknown48;
    char Unknown49[2];
    bool Unknown4B;
};

class Class_10D9B090
{
public:
    char Unknown00[0xB8];
    bool UnknownB8;
};

Class_10D9B090* FUN_10d9dcb0();

class Class_10BCFE10
{
public:
    void FUN_10bcfbd0();
    void FUN_10bcfe10(int A);
};

class FArchive
{
public:
    virtual ~FArchive();
    virtual void Serialize(void* V, int Length);
};

class TimeManager
{
public:
    static TimeManager* Instance();
    double GetGameTime();
};

class Class_10E8BE68
{
public:
    virtual void FUN_10bca010(FArchive& Ar);
};

class Class_10E94578 : public Class_10E8BE68
{
public:
    void FUN_10bc5b50();
};

class Class_10E92A00 : public Class_10E94578
{
public:
    virtual void Virtual1();
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
    virtual void Virtual23();
    virtual void Virtual24();
    virtual void FUN_10bcec90();
    virtual void Virtual26();
    virtual void Virtual27();
    virtual void Virtual28();
    virtual void Virtual29();
    virtual void Virtual30();
    virtual void Virtual31();
    virtual void Virtual32();
    virtual void Virtual33();
    virtual void Virtual34();
    virtual void Virtual35();
    virtual void Virtual36();
    virtual void Virtual37();
    virtual void Virtual38();
    virtual void Virtual39();
    virtual void Virtual40();
    virtual void Virtual41();
    virtual void Virtual42();
    virtual void Virtual43();
    virtual void Virtual44();
    virtual void Virtual45();
    virtual void Virtual46();
    virtual void Virtual47();
    virtual void Virtual48();
    virtual void Virtual49();
    virtual void Virtual50();
    virtual void Virtual51();
    virtual void Virtual52();
    virtual void Virtual53();
    virtual void Virtual54();
    virtual void Virtual55();
    virtual void Virtual56();
    virtual void Virtual57();
    virtual void Virtual58();
    virtual void Virtual59();
    virtual void Virtual60();
    virtual void Virtual61();
    virtual void Virtual62();
    virtual void Virtual63();
    virtual void FUN_10bce9b0(FArchive& Ar);

    char Unknown04[0x3C];
    double Unknown40;
    double Unknown48;
    int Unknown50;
};

// FUNCTION: 0x10BCEC90 ?FUN_10bcec90@Class_10E92A00@@UAEXXZ
void Class_10E92A00::FUN_10bcec90()
{
    if (Unknown48 > 0.0 && TimeManager::Instance()->GetGameTime() > Unknown48)
        FUN_10bc5b50();
}

// FUNCTION: 0x10BCEF30 ?FUN_10bcef30@Class_10E92C38@@UAEXXZ
void Class_10E92C38::FUN_10bcef30()
{
    if (Unknown4B && Unknown48)
    {
        FUN_10bced10();
        Unknown48 = false;
    }
}

// FUNCTION: 0x10BCFE10 ?FUN_10bcfe10@Class_10BCFE10@@QAEXH@Z
void Class_10BCFE10::FUN_10bcfe10(int A)
{
    if (!FUN_10d9dcb0()->UnknownB8)
        FUN_10bcfbd0();
}
