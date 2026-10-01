// Game/Unsorted_10BDFAA0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10BC4160
{
public:
    virtual void Virtual0();

    int FUN_10bc4160();
};

class Class_10E95170 : public Class_10BC4160
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void FUN_10be1620();
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
    virtual void Virtual64();
    virtual void Virtual65();
    virtual void Virtual66();
    virtual void Virtual67();
    virtual void Virtual68();
    virtual bool Virtual69();

    void FUN_10bdfef0();
};

extern void* DAT_10e95780[];

class Class_10E90D70
{
public:
    Class_10E90D70(int A, int B);

    void** Unknown00;
    int Unknown04[15];
};

class Class_10E95780 : public Class_10E90D70
{
public:
    Class_10E95780* FUN_10be1820(int A, int B);

    int Unknown40;
    int Unknown44;
    bool Unknown48;
    bool Unknown49;
    char Unknown4A[2];
    int Unknown4C;
};

// FUNCTION: 0x10BE1620 ?FUN_10be1620@Class_10E95170@@UAEXXZ
void Class_10E95170::FUN_10be1620()
{
    if (!Virtual69())
    {
        FUN_10bc4160();
        FUN_10bdfef0();
    }
}

// FUNCTION: 0x10BE1820 ?FUN_10be1820@Class_10E95780@@QAEPAV1@HH@Z
Class_10E95780* Class_10E95780::FUN_10be1820(int A, int B)
{
    this->Class_10E90D70::Class_10E90D70(A, B);
    Unknown40 = 0;
    Unknown44 = 0;
    Unknown48 = false;
    Unknown49 = false;
    Unknown4C = 0;
    Unknown00 = DAT_10e95780;
    return this;
}
