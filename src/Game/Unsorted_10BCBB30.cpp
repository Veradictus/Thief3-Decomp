// Game/Unsorted_10BCBB30.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class FArchive
{
public:
    virtual ~FArchive();
    virtual void Serialize(void* V, int Length);

    char Unknown04[8];
    int Unknown0C;
};

class Class_10C17360
{
public:
    void FUN_10c17360();
};

struct Struct_10BCBD10
{
    char Unknown00[0xAC];
    Class_10C17360 UnknownAC;
};

class Class_10E94578
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
    virtual void FUN_10bcac50(int A, int B, int C, int D, int E);

    void FUN_10bc5b50();
    void FUN_10bcb850(FArchive& Ar);
};

class Class_10E92118 : public Class_10E94578
{
public:
    virtual void FUN_10bcbd10(int A, int B, int C, int D, int E);
    virtual void Virtual25();
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
    virtual void FUN_10bcbcc0(FArchive& Ar);

    Struct_10BCBD10* Unknown04;
    char Unknown08[0x54];
    bool Unknown5C;
    char Unknown5D[3];
    int Unknown60;
    int Unknown64;
};

// FUNCTION: 0x10BCBCC0 ?FUN_10bcbcc0@Class_10E92118@@UAEXAAVFArchive@@@Z
void Class_10E92118::FUN_10bcbcc0(FArchive& Ar)
{
    FUN_10bcb850(Ar);
    Ar.Serialize(&Unknown5C, 1);
    Ar.Serialize(&Unknown64, 4);
    if (Ar.Unknown0C >= 0x72)
        Ar.Serialize(&Unknown60, 4);
}
