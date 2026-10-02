// Game/Unsorted_10C2F340.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern "C" int __cdecl sprintf(char* Out, const char* Format, ...);

struct Struct_10FF66B0
{
    const char* Unknown00;
    char Unknown04[8];
    int Unknown0C;
    char Unknown10[4];
};

extern Struct_10FF66B0 DAT_10ff66b0[];

class Class_10E9AC80
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
    virtual void FUN_10c2f4a0(char* Buffer);
    virtual void Virtual36();
    virtual void Virtual37();
    virtual int Virtual38();
};

// FUNCTION: 0x10C2F4A0 ?FUN_10c2f4a0@Class_10E9AC80@@UAEXPAD@Z
void Class_10E9AC80::FUN_10c2f4a0(char* Buffer)
{
    sprintf(Buffer, "%s: %d", DAT_10ff66b0[Virtual38()].Unknown00, DAT_10ff66b0[Virtual38()].Unknown0C);
}
