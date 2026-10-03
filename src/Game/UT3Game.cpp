// Game/UT3Game.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class UT3Game_Unknown5C
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5(int A);
};

class UT3Game_Unknown74
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5();
    virtual void Virtual6();
    virtual void Virtual7(int A, int B);
};

class UT3Game
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
    virtual void Virtual23();
    virtual void Virtual24();
    virtual void Virtual25();
    virtual void Virtual26();
    virtual void Virtual27();
    virtual void Virtual28();
    virtual void Virtual29();
    virtual void Virtual30();
    virtual void FUN_10b13bc0(int A);
    virtual void Virtual32();
    virtual void Virtual33();
    virtual void Virtual34();
    virtual void Virtual35();
    virtual void Virtual36();
    virtual void Virtual37();
    virtual void Virtual38();
    virtual void FUN_10b14f70(int A, int B);

    char Unknown04[0x50];
    int Unknown54;
    char Unknown58[4];
    UT3Game_Unknown5C** Unknown5C;
    char Unknown60[0xC];
    int Unknown6C;
    char Unknown70[4];
    UT3Game_Unknown74** Unknown74;
};

// FUNCTION: 0x10B13BC0 ?FUN_10b13bc0@UT3Game@@UAEXH@Z
void UT3Game::FUN_10b13bc0(int A)
{
    for (int i = 0; i < Unknown54; i++)
        Unknown5C[i]->Virtual5(A);
}

// FUNCTION: 0x10B14F70 ?FUN_10b14f70@UT3Game@@UAEXHH@Z
void UT3Game::FUN_10b14f70(int A, int B)
{
    for (int i = 0; i < Unknown6C; i++)
        Unknown74[i]->Virtual7(A, B);
}
