// Game/Unsorted_10A1FB80.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10905A90_Member
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2(int A, int B, int C, int D, int E);
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5(void* Block);
};

Class_10905A90_Member* FUN_10905aa0();

class Class_10A21480
{
public:
    void FUN_10a20f60(int Count);
    void FUN_10a21480();

    int Unknown00;
    int Unknown04;
    void* Unknown08;
};

class Class_10A1FD90
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
    virtual void Virtual31();
    virtual void Virtual32();
    virtual void Virtual33();
    virtual void Virtual34();
    virtual void Virtual35();
    virtual void Virtual36();
    virtual void Virtual37(int A, int B);

    void FUN_10a1fd90(int A, int B, int C);

    char Unknown04[0x34];
    int Unknown38;
    char Unknown3C[0xC];
    int Unknown48;
};

// FUNCTION: 0x10A1FD90 ?FUN_10a1fd90@Class_10A1FD90@@QAEXHHH@Z
void Class_10A1FD90::FUN_10a1fd90(int A, int B, int C)
{
    int Offset = Unknown38 * C + Unknown48;
    Virtual37(Offset + A, B ? Offset + B : 0);
}

// FUNCTION: 0x10A21480 ?FUN_10a21480@Class_10A21480@@QAEXXZ
void Class_10A21480::FUN_10a21480()
{
    FUN_10a20f60(0);
    if (Unknown04)
    {
        FUN_10905aa0()->Virtual5(Unknown08);
        Unknown08 = 0;
        Unknown04 = 0;
    }
}
