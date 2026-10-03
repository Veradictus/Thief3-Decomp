// Game/Unsorted_10BAA470_3.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class AAIPawn;

class Class_10BABED0;

struct Struct_10B9BCA0_Unknown118
{
    char Unknown00[0x10];
    Class_10BABED0* Unknown10;
};

class Class_10B9BCA0
{
public:
    char Unknown00[0x118];
    Struct_10B9BCA0_Unknown118* Unknown118;
};

Class_10B9BCA0* FUN_10baa660(AAIPawn* Pawn);

class Class_10BAA6B0_Param
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
    virtual int Virtual34();

    char Unknown04[0xBC];
    int Unknown0C0;
};

// FUNCTION: 0x10BAA6B0 ?FUN_10baa6b0@@YAPAVClass_10BABED0@@PAVClass_10BAA6B0_Param@@@Z
Class_10BABED0* FUN_10baa6b0(Class_10BAA6B0_Param* Param)
{
    if (Param->Unknown0C0 && !Param->Virtual34())
    {
        Class_10B9BCA0* Info = FUN_10baa660((AAIPawn*)Param);
        if (Info && Info->Unknown118)
            return Info->Unknown118->Unknown10;
    }
    return 0;
}
