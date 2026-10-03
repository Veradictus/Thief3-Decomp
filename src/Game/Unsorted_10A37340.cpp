// Game/Unsorted_10A37340.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10992030
{
public:
    void FUN_10992030(int A, int B, int C);

    char Unknown00[0xB0];
    int UnknownB0;
};

class Struct_10AA3520_Unknown78
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
    virtual void Virtual16(Class_10992030* A);
};

struct Struct_10AA3520
{
    char Unknown00[0x78];
    Struct_10AA3520_Unknown78* Unknown78;
};

extern Struct_10AA3520* DAT_10f35dec;

class UPhysicsSubsystem
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
    virtual void Virtual37();
    virtual void Virtual38();
    virtual void Virtual39();
    virtual void Virtual40();
    virtual void Virtual41();
    virtual void Virtual42(Class_10992030* A);
};

class UEngine
{
public:
    virtual void Virtual0();

    char Unknown04[0x3C];
    UPhysicsSubsystem* Physics;
};

extern UEngine* GEngine;

// FUNCTION: 0x10A37340 ?FUN_10a37340@@YA_NPAVClass_10992030@@@Z
bool FUN_10a37340(Class_10992030* Obj)
{
    Obj->FUN_10992030(0, 0, 0);
    DAT_10f35dec->Unknown78->Virtual16(Obj);
    if (!Obj->UnknownB0)
        return false;
    GEngine->Physics->Virtual42(Obj);
    return true;
}
