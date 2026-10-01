// Game/Unsorted_109E6110.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_109081E0
{
public:
    Class_109081E0& operator=(const Class_109081E0& Other);

    void* Unknown00;
};

class Class_10E5B2C0
{
public:
    virtual void FUN_109e66e0(const Class_109081E0& Value);

    char Unknown04[0xD4];
    Class_109081E0 UnknownD8;
};

class Class_10BFBD70
{
public:
    void FUN_10bfbd70(int NewCount);

    int Count;
    int Unknown04;
    int* Data;
};

class Class_10E5B588
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
    virtual void FUN_109e6110(int A, Class_10BFBD70* Array);

    char Unknown04[0x120];
    int Unknown124;
};

struct Struct_109E6220_Item {
    char Unknown00[8];
    int Unknown08;
};

class Class_109E6220 {
public:
    char Unknown00[0x8C];
    Struct_109E6220_Item** Unknown8C;
    int Unknown90;

    int FUN_109e6220();
};

// FUNCTION: 0x109E6110 ?FUN_109e6110@Class_10E5B588@@UAEXHPAVClass_10BFBD70@@@Z
void Class_10E5B588::FUN_109e6110(int A, Class_10BFBD70* Array)
{
    if (Array)
    {
        int Index = Array->Count;
        Array->FUN_10bfbd70(Index + 1);
        Array->Data[Index] = Unknown124;
    }
}

// FUNCTION: 0x109E6220 ?FUN_109e6220@Class_109E6220@@QAEHXZ
int Class_109E6220::FUN_109e6220()
{
    if (Unknown90 == 0)
        return 0;
    return (*Unknown8C)->Unknown08;
}

// FUNCTION: 0x109E66E0 ?FUN_109e66e0@Class_10E5B2C0@@UAEXABVClass_109081E0@@@Z
void Class_10E5B2C0::FUN_109e66e0(const Class_109081E0& Value)
{
    UnknownD8 = Value;
}
